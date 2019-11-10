#include<iostream>
using namespace std;


template <typename Type>
class Single_node {
    private:
        Type element;
        Single_node *next_node;
    public:
        Single_node( Type = nullptr, Single_node * = nullptr );
        Type retrieve() const;
        Single_node<Type> *next() const;
        void Setnext(Single_node*);
};

template <typename Type>
Single_node<Type>::Single_node( Type e, Single_node *n ):element( e ),next_node( n ) { }

template <typename Type>
Type Single_node<Type>::retrieve() const {return element;}

template <typename Type>
Single_node<Type>* Single_node<Type>::next() const {return next_node;}

template <typename Type>
void Single_node<Type>::Setnext(Single_node* node){
    next_node=node;
}


template <typename Type>
class Single_list {
    public:
        Single_node<Type> *list_head;
        Single_list();
        void push_front( Type );
        Type front() const;
        Single_node<Type> *head() const;
        bool empty() const;
        Type pop_front();
};

template <typename Type>
Single_list<Type>::Single_list():list_head( nullptr ) {}

template <typename Type>
Single_node<Type> *Single_list<Type>::head() const {return list_head;}

template <typename Type>
Type Single_list<Type>::front() const {
    return head()->retrieve();
}

template <typename Type>
bool Single_list<Type>::empty() const {return ( list_head == nullptr );}

template <typename Type>
void Single_list<Type>::push_front( Type n ) {
    if ( empty() ) {
        list_head = new Single_node<Type>( n, nullptr );
    } else {
        list_head = new Single_node<Type>( n, head() );
    } 
}

template <typename Type>
Type Single_list<Type>::pop_front() {
    Type e = front();
    Single_node<Type> *ptr = list_head;
    list_head = list_head->next();
    delete ptr;
    return e;
}

class Simple_tree {
public:
    int max_decay;
    int power;
    int name;
    int reduce;
    int level;
    Simple_tree *parent_node;
    Single_list<Simple_tree *> children;
    Simple_tree(int,int,Simple_tree*,int);
    Simple_tree();
    bool available();
    void reset(int);
    int count();
    void levelupdate(int = 0);
};
Simple_tree::Simple_tree(int name1,int reduce1,Simple_tree* parent,int l){
    max_decay=0;
    name=name1;
    reduce=reduce1;
    parent_node=parent;
    level=l;
    children=Single_list<Simple_tree *>();
}
Simple_tree::Simple_tree(){
    max_decay=0;
    name=0;
    reduce=0;
    parent_node=nullptr;
    level=0;
    children=Single_list<Simple_tree *>();
}
void Simple_tree::levelupdate(int n){
    this->level=n;
    for(Single_node<Simple_tree*>* i=this->children.list_head;i!=nullptr;i=i->next()){
        i->retrieve()->levelupdate(n+1);
    }
}
bool Simple_tree::available(){
    if(this->children.list_head==nullptr) return (this->power>=0);
    else{
        for(Single_node<Simple_tree*>* i=this->children.list_head;i!=nullptr;i=i->next()){
            if(!(i->retrieve()->available())) return false;
        }
        return true;
    }
}
void Simple_tree::reset(int pow){
    this->power=pow;
    for(Single_node<Simple_tree*>* i=this->children.list_head;i!=nullptr;i=i->next()){
        i->retrieve()->reset(pow-i->retrieve()->reduce);
    }
}

int main(){
    int n;
    int max_reduce=0;
    cin>>n;
    Simple_tree** trees=new Simple_tree*[n];
    int* middle=new int[n];
    for(int i=0;i<n;i++){
        trees[i]=new Simple_tree(0,0,nullptr,0);
    }
    int k=0;
    int** node=new int*[n];
    for(int i=0;i<n;i++){
        node[i] = new int[1];
    }
    node[0][0]=0;
    int *width=new int[n];
    width[0]=1;
    for(int i=1;i<n;i++){
        width[i] = 0;
    }
    int max_level=0;
    int max_name;
    for(int i=0;i<n;i++){
        int degree;
        cin>>degree;
        if(degree!=0){
            middle[k]=i;
            k++;
        }
        for(int j=0;j<degree;j++){
            int name,reduce;
            cin>>name;
            cin>>reduce;
            trees[name-1]->name=name;
            trees[name-1]->reduce=reduce;
            trees[name-1]->parent_node=trees[i];
            trees[i]->children.push_front(trees[name-1]);
            if(reduce>max_reduce){
                max_reduce=reduce;
                max_name=name-1;            
            }
        }
    }
    trees[0]->levelupdate(0);
    for(int i=1;i<n;i++){
        int l=trees[i]->level;
        if(l>max_level) max_level=l;
        node[l][width[l]]=i;
        width[l]++;
        int*temp=node[l];
        node[l]=new int[width[l]+1];
        for(int q=0;q<width[l];q++){
            node[l][q]=temp[q];
        }
        delete temp;
    }
    int pow;
    cin>>pow;
    if(max_reduce>pow){
        cout<<"No solution."<<endl;
        return 0;
    }
    trees[0]->reset(pow);
    int mini_amp=0;
    for(int i=max_level;i>=1;i--){
        for(int j=0;j<width[i];j++){
            if(trees[node[i][j]]->max_decay+trees[node[i][j]]->reduce>pow){
                mini_amp++;
                trees[node[i][j]]->max_decay=0;
            }
            if(trees[node[i][j]]->max_decay+trees[node[i][j]]->reduce>trees[node[i][j]]->parent_node->max_decay){
                trees[node[i][j]]->parent_node->max_decay=trees[node[i][j]]->max_decay+trees[node[i][j]]->reduce;
            }
        }
    }
    cout<<mini_amp<<endl;
    return 0;
}
