#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class Node{
    public:
    char content;
    Node *child0, *child1;
    Node(char c):content(c), child0(0), child1(0){}
    Node(const Node& node):content(node.content){
        if(node.child0!=0) child0=new Node(*(node.child0)); else this->child0=0;
        if(node.child1!=0) child1=new Node(*(node.child1)); else this->child1=0;}
    void makeChild(char type){
        if(type=='0') child0=new Node(type);
        else child1=new Node(type);}
    void deviation(int depth, double& deviation_sum, double& avg){
        if(child0!=0){ child0->deviation(++depth, deviation_sum, avg);depth--;}
        if(child1!=0){ child1->deviation(++depth, deviation_sum, avg);depth--;}
        if(child0==0 && child1==0) deviation_sum+=(depth-avg)*(depth-avg);}
    void write(int depth, fstream* output){
        if(child1!=0){child1->write(++depth, output);depth--;}
        for(int i=0;i<(3*(depth+1));i++) *output << '-';
        (*output) << content << '(' << depth << ')' << endl;
        if(child0!=0){ child0->write(++depth, output);depth--;}}
    void calculate(int depth, int& maxdepth, int& avg_c, int& avg_sum){
        if(child1!=0){child1->calculate(++depth, maxdepth, avg_c, avg_sum);
        if(depth>maxdepth) maxdepth=depth;
        depth--;}
        else if(child0==0){++avg_c;avg_sum+=depth;}
        if(child0!=0){ child0->calculate(++depth, maxdepth, avg_c, avg_sum);
        if(depth>maxdepth) maxdepth=depth;
        depth--;}}
    void AllIn(int depth, int& maxdepth, int& avg_c, int& avg_sum, fstream* output){
        if(child1!=0){child1->AllIn(++depth, maxdepth, avg_c, avg_sum, output);
        if(depth>maxdepth) maxdepth=depth;
        depth--;}
        else if(child0==0){++avg_c;avg_sum+=depth;}
        for(int i=0;i<(3*(depth+1));i++) *output << '-';
        (*output) << content << '(' << depth << ')' << endl;
        if(child0!=0){ child0->AllIn(++depth, maxdepth, avg_c, avg_sum, output);
        if(depth>maxdepth) maxdepth=depth;
        depth--;}}
};

class Tree{
    public:
    Node *root, *actual;
    int maxdepth, avg_c, avg_sum;
    double avg, deviation, deviation_sum;
    Tree (){
        root = new Node('/');
        actual = root;
        maxdepth =  avg_c = avg_sum = 0;
        avg = deviation = deviation_sum = 0.0;}
    Tree(const Tree& t): maxdepth(t.maxdepth), avg_c(t.avg_c), avg_sum(t.avg_sum), avg(t.avg), deviation(t.deviation), deviation_sum(t.deviation_sum) {
        root = new Node(*(t.root));
        actual = root;}
    Tree(Tree&& t): maxdepth(t.maxdepth), avg_c(t.avg_c), avg_sum(t.avg_sum), avg(t.avg), deviation(t.deviation), deviation_sum(t.deviation_sum) {
        actual = root = t.root;
        t.root = 0;}
    Tree& operator= (Tree&& t){
        avg_c=(t.avg_c); avg_sum=(t.avg_sum); avg=(t.avg); deviation=(t.deviation); deviation_sum=(t.deviation_sum);
        freeNodesFrom(root);
        root = t.root;
        actual = t.actual;
        t.root=0;}
    Tree& operator= (const Tree& t) {
        avg_c=(t.avg_c); avg_sum=(t.avg_sum); avg=(t.avg); deviation=(t.deviation); deviation_sum=(t.deviation_sum);
        freeNodesFrom(root);
        root = new Node(*(t.root));
        actual = t.actual;}
    ~Tree(){freeNodesFrom(root);}
    void freeNodesFrom(Node *node){
      if(node!=0){
        freeNodesFrom(node->child0);
        freeNodesFrom(node->child1);
        delete node;}}
    void operator<< (char c) {
        if((c=='0' && actual->child0==0) || (c=='1' && actual->child1==0)){
        actual->makeChild(c);
        actual = root;
        return;}
        if(c=='0'){actual = actual->child0;return;}
        actual = actual->child1;
        return;}
    void write(fstream* output){
        root->write(0, output);
        if(avg_c==0) *(output)<<"Stats not ready";
        else *(output) << "depth = " << maxdepth << endl << "mean = " << avg << endl << "var = " << deviation <<endl; }
    void calculate(){
        root->calculate(0, maxdepth, avg_c, avg_sum);
        avg=avg_sum/(double)avg_c;
        root->deviation(0, deviation_sum, avg);
        deviation = (avg_c>1) ? sqrt(deviation_sum/(double)(avg_c-1)) : sqrt(deviation_sum);}
    void doIt(fstream* output){
        root->AllIn(0, maxdepth, avg_c, avg_sum, output);
        avg=avg_sum/(double)avg_c;
        root->deviation(0, deviation_sum, avg);
        deviation = (avg_c>1) ? sqrt(deviation_sum/(double)(avg_c-1)) : sqrt(deviation_sum);
        *(output) << "depth = " << maxdepth << endl << "mean = " << avg << endl << "var = " << deviation <<endl;}
};

int main(int arg_c, char* args[]){
    if(arg_c!=4) return -1;
    char* in = *++args;
    if (*((*++args) + 1) != 'o')return -2;
    fstream *input, *output;
    input=new fstream(in, ios_base::in);
    if(!input) return -3;
    Tree tree;
    output=new fstream(*++args, ios_base::out);
    bool comment = false;
    unsigned char asd;
    while ((input->read ((char*) &asd, sizeof (unsigned char)))){
        if (asd == 0x3e){comment = true;continue;}
        if (asd == 0x0a){comment = false;continue;}
        if (comment)continue;
        if (asd == 0x4e)continue;
        for (int l = 0;l < 8; ++l){
            if (asd & 0x80) tree << '1';
            else tree << '0';
            asd <<= 1;}}
    tree.doIt(output);
    output->close();
    input->close();
    delete input;
    delete output;
return 0;}
