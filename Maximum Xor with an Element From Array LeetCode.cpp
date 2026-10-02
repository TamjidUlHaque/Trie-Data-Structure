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

    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        
        Trie memory ; sort(nums.begin(),nums.end()) ;
        vector<vector<int>> questions ;

        for(int i = 0 ; i < queries.size() ; i++){
            questions.push_back({queries[i][1],queries[i][0],i}) ;
        }

        sort(questions.begin(),questions.end()) ;

        vector<int> ans(queries.size(),0) ; int ptr = 0 ;

        for(auto &question:questions){
            int limit = question[0] ;
            int value = question[1] ;
            int idx = question[2] ;
            while(ptr < nums.size() and nums[ptr] <= limit){
                memory.insert(nums[ptr++]) ;
            }
            if(ptr == 0){
                ans[idx] = -1 ;
            }else{
                ans[idx] = memory.getMaxXor(value) ;
            }
        }

        return ans ;
    }
};