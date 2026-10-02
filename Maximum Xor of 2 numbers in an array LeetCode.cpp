class Solution {
public:

    struct Node{
        Node *links[2] ;

        bool present(int state){
            return (links[state] != NULL) ;
        }

        void create(int state, Node* node){
            links[state] = node ;
        }

        Node* move(int state){
            return (links[state]) ;
        }
        
    };

    class Trie {
    public:
        Node* root ;
        
        Trie() {
            root = new Node() ;
        }
        
        void insert(int number) {
            Node* temp = root ;
            for(int posn = 31 ; posn >= 0 ; posn--){
                int state = ((number >> posn) & 1) ;
                if(!temp->present(state)){
                    temp->create(state,new Node()) ;
                }
                temp = temp->move(state) ;
            }
        }

        int getMaxXor(int number){
            Node* temp = root ; int ans = 0 ;

            for(int posn = 31 ; posn >= 0 ; posn--){
                int state = ((number >> posn) & 1) ;

                if(temp->present(state ^ 1)){
                    ans |= (1 << posn) ;
                    temp = temp->move(state ^ 1) ;
                }else{
                    temp = temp->move(state) ;
                }
            }
            return ans ;
        }
        
    };

    int findMaximumXOR(vector<int>& nums) {
        Trie memory ;
        for(auto &num:nums) memory.insert(num) ;

        int ans = 0 ;

        for(auto &num:nums){
            ans = max(ans,memory.getMaxXor(num)) ;
        }

        return ans ;
    }
};