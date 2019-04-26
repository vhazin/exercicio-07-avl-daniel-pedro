#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no {
	int key;
	struct no *left;
	struct no *right;
	int left_temp;
	int right_temp;
	int alt;
} no;

int max(int a, int b) {
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

int alt(no *root) {
	if(root==NULL){
		return -1;
	}
	else{
		return root->alt;
	}
}

no *new_no (int key, int left_temp, int right_temp) {
	no *tmp_no = (no *) malloc( sizeof(no) );
	tmp_no -> key = key;
	tmp_no -> left = NULL;
	tmp_no -> right = NULL;
	tmp_no -> alt = 1;
	tmp_no -> left_temp = left_temp;
	tmp_no -> right_temp = right_temp;
	return tmp_no;
}
//rotacao direita simples
no *RR (no *y) {
	no *x = y -> left;
	no *T2 = x -> right;

	x -> right = y;
	y -> left = T2;

	y -> alt = max( alt(y -> left), alt(y -> right) ) + 1;
	x -> alt = max( alt(x -> left), alt(x -> right) ) + 1;
	
    if (T2 != NULL) {
        y -> left_temp = T2 -> left_temp + T2 -> right_temp + 1;
        
    }
    else {
        y -> left_temp = 0;
        x -> right_temp = y -> left_temp + y -> right_temp + 1;
    }
	return x;
}
//rotacao esquerda simples
no *LL (no *x) {
	no *y = x -> right;
	no *T2 = y -> left;

	y -> left = x;
	x -> right = T2;

	x -> alt = max( alt(x -> left), alt(x -> right) ) + 1;
	y -> alt = max( alt(y -> left), alt(y -> right) ) + 1;

	if (T2 != NULL){ 
		x -> right_temp = T2 -> left_temp + T2 -> right_temp + 1;
	} 
	else{ 
		x -> right_temp = 0;
		y -> left_temp = x -> left_temp + x -> right_temp + 1;
	}
	return y;
}
//fator de balanceamento
int FB (no *root) {
	if (root == NULL) {
		return 0;
	}
	else {
		return alt(root -> left) - alt(root -> right);
}
}
//inserir no
no *inserir(no *root, int key) {

	if (root == NULL) {
		return new_no(key, 0, 0);
	}
	if (key < root -> key) {
		root -> left = inserir(root -> left, key);
		root -> left_temp++;
	}
	else if (key > root -> key) {
		root -> right = inserir(root -> right, key);
		root -> right_temp++;
	}
	else { 
		return root;
  }
  	root -> alt = max( alt(root -> left), alt(root -> right) ) + 1;

	int balance = FB(root);

	// 4 cases for unbalanced no
	if ( (balance > 1) && (key < root -> left -> key) ) return RR(root);

	if ( (balance < -1) && (key > root -> right -> key) ) return LL(root);

	if ( (balance > 1) && (key > root -> left -> key) ) {
		root -> left = LL(root -> left);
		return RR(root);
	}

	if ( (balance < -1) && (key < root -> right -> key) ) {
		root -> right = RR(root -> right);
		return LL(root);
	}

	return root;
}

int flag;

int key_check (no *root, int key) {
	if (root != NULL) {
		
		if (key > root -> key) return root -> left_temp + 1 + key_check(root -> right, key);
		else if (key < root -> key) return key_check(root -> left, key);
		else return root -> left_temp;
	} else {

		flag = 1;
		return -1;
	};
}
	
void em_ordem (no *root) {
	if (root != NULL) {
		printf("%d %d %d\n", root -> key, root -> left_temp, root -> right_temp);
		em_ordem(root -> left);
		em_ordem(root -> right);
	}
}



int main () {
	
	int n;
	scanf("%d", &n);
	no *root = NULL;
	for (int i = 0; i < n; i++) {
		int var;
		int num;
		scanf("%d%d", &var, &num);
		if (var == 1) {
			
			root = inserir(root, num);
		}
		if (var == 2) {
			
			flag = 0;
			int rank = key_check(root, num) + 1;
			if (flag) printf("Data tidak ada\n"); else printf("%d\n", rank);
		}
		
	}
	
	return 0;
}
