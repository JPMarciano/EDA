#include <cstdlib>
#include <iostream>

int* merge(int a[], int b[], int tam1, int tam2){
	int *result = new int[tam1 + tam2];

	std::cout << "address:" << result << "\n";
	
	int x=0;
	int j=0;
	
	for(int i=0; i<tam1; i++){
		while(a[i]>=b[j] && j<tam2){
			result[x] = b[j];
			x++;
			j++;
		}
		result[x]=a[i];
		x++;
	}
	while(j<tam2){
		result[x]=b[j];
		x++;
		j++;
	}
	
	for(int i=0; i<15; i++)
		std::cout << result[i] << "\n";
	
	return result;
}

int* merge_sort(int a[], int tam){
	
	int *b;
	b = merge_sort(a, tam/2);
	int *c;
	c = merge_sort(&a[tam/2], tam - tam/2);
	return merge(b, c, tam/2, tam-tam/2);
}

int* insertion_sort(int a[], int tam){
	
}

int main(){
	int a[10] = {9,2,4,6,7,8,4,232,2,3};
	
	int *result;
	
	result = merge_sort(a,10);
	
	for(int i=0; i<10; i++){
		std::cout << result[i] << "\n";
	}
	
	delete[] result;	
}

