#include <cstdio>
struct node{
    int sum, num;
    node *l, *r;
    node():sum(0),num(0),l(NULL),r(NULL){}
    int l_sum(){ return l ? l->sum : 0; }
    int r_sum(){ return r ? r->sum : 0; }
    int l_num(){ return l ? l->num : 0; }
    int r_num(){ return r ? r->num : 0; }
}*segTree[100010];
 
node* build(int l, int r){
    if(l == r) return new node();
    node* root = new node();
    int m = l+r >> 1;
    root -> l = build(l, m);
    root -> r = build(m+1, r);
    return root;
}
  
node* new_tree(node* T, int l, int r, int p){
    int m = l+r >> 1;
    node *root = new node();
    root->num = T->num+1;
    root->sum = T->sum+p;
    if(l == r) return root;
    else{
        if(p<=m){
            root->r = T->r;
            root->l = new_tree(T->l, l, m, p);
        }else{
            root->l = T->l;
            root->r = new_tree(T->r, m+1, r, p);
        }
    }
    return root;
}
  
int Solve(int S, node* a, node* b, int l, int r){
    int m = l+r >> 1;
    if(l == r) return S/m;
    int price = a->sum - b->sum;
    int l_price = a->l_sum() - b->l_sum();
    int r_price = a->r_sum() - b->r_sum();
    if(price <= S) return a->num - b->num;
    if(l_price <= S) return a->l_num() - b->l_num() + Solve(S-l_price, a->r, b->r, m+1, r);
    return Solve(S, a->l, b->l, l, m);
}
  
int main(){
    segTree[0] = build(0, 16383);
    int T;
    scanf("%d", &T);
    while(T--){
        int N, Q;
        scanf("%d %d", &N, &Q);
        for(int i = 1; i <= N; ++i){
            int price;
            scanf("%d", &price);
            segTree[i] = new_tree(segTree[i-1], 0, 16383, price);
        }
        int value = 0;
        for(int i = 0; i < Q; ++i){
            int L, R, S;
            scanf("%d %d %d", &L, &R, &S);
            int res = Solve(S, segTree[R], segTree[L-1], 0, 16383);
            value ^= (res + i + 1);
        }
        printf("%d\n", value);
    }
    return 0;
}
