struct Node{
    Node *links[26] ;
    bool flag = false ;

    bool present(char ch){
        return (links[ch-'a'] != NULL) ;
    }

    void create(char ch, Node* node){
        links[ch-'a'] = node ;
    }

    Node* move(char ch){
        return (links[ch-'a']) ;
    }

    void complete(){
        flag = true ;
    }

    bool isEnd(){
        return flag ;
    }
};

class Trie {
private: Node* root ;
public:
    Trie() {
        root = new Node() ;
    }
    
    void insert(string word) {
        Node* temp = root ;
        for(int i = 0 ; i < word.size() ; i++){
            if(!temp->present(word[i])){
                temp->create(word[i],new Node()) ;
            }
            temp = temp->move(word[i]) ;
        }
        temp->complete() ;
    }
    
    bool search(string word) {
        Node* temp = root ;
        for(int i = 0 ; i < word.size() ; i++){
            if(!temp->present(word[i])){
                return false ;
            }
            temp = temp->move(word[i]) ;
        }
        return temp->isEnd() ;
    }
    
    bool startsWith(string word) {
        Node* temp = root ;
        for(int i = 0 ; i < word.size() ; i++){
            if(!temp->present(word[i])){
                return false ;
            }
            temp = temp->move(word[i]) ;
        }
        return true ;
    }
};
