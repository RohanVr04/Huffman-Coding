#include<iostream>
#include<string>
#include<queue>
#include<unordered_map>
using namespace std;

class Node{
    public:

    char data;
    int cost;
    Node* left;
    Node* right;

    Node(char data,int cost){
        this->data = data;
        this->cost = cost;
        this->left = NULL;
        this->right = NULL;
    }

    bool operator<(Node* other){
        return this->cost > other->cost;
    }

    struct Compare {
        bool operator()(const Node* a, const Node* b) const {
            return a->cost > b->cost; 
        }
    };

};

class HuffmanCoder{
    private:
        unordered_map<char,string>encoder;
        unordered_map<string,char>decoder;

    public:
        HuffmanCoder(string feeder){
            unordered_map<char,int>fmap;
            for(int i=0;i<feeder.length();i++){
                fmap[feeder[i]]++;
            }

            priority_queue<Node*,vector<Node*>,Node::Compare>minHeap;
            for(auto i:fmap){
                Node* node = new Node(i.first,i.second);
                minHeap.push(node);
            }

            while(minHeap.size()!=1){
                Node* first = minHeap.top();
                minHeap.pop();
                Node* second = minHeap.top();
                minHeap.pop();

                Node* newNode = new Node('\0',first->cost+second->cost);
                newNode->left = first;
                newNode->right = second;
                minHeap.push(newNode);
            }

            Node* root = minHeap.top();
            initEncoderDecoder(root,"");
        }
    private:
        void initEncoderDecoder(Node*root,string osf){
            if(root==NULL){
                return;
            }

            if(root->left==NULL and root->right==NULL){
                encoder[root->data] = osf;
                decoder[osf] = root->data;
            }
            initEncoderDecoder(root->left,osf+"0");
            initEncoderDecoder(root->right,osf+"1");
        }

    public:

        string encode(string source){
            string ans = "";
            for(int i=0;i<source.length();i++){
                ans+=encoder[source[i]];
            }

            return ans;
        }

        string decode(string codedString){
            string ans = "";
            string key = "";
            for(int i=0;i<codedString.length();i++){
                key += codedString[i];
                if(decoder.count(key)){
                    ans+=decoder[key];
                    key = "";
                }
            }
            return ans;
        }
};



int main(){
    string str;
    cin>>str;

    HuffmanCoder* hf = new HuffmanCoder(str);
    string cs = hf->encode(str);
    string ds = hf->decode(cs);
    int compression_percentage = ((cs.size()*100)/(str.size()*8));
    cout<<"Compressed String: "<<cs<<endl;
    cout<<"Decompressed String: "<<ds<<endl;
    cout << "Percentage Compression: " <<compression_percentage<<endl;



}