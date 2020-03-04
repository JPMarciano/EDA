#include <cstdlib>
#include <iostream>
#include <chrono>

void print(int a[], int tam){
	for(int i=0; i<tam; i++){
		std::cout << a[i] << "\n";
	}
}

int* merge(int a[], int b[], int tam1, int tam2){
	int *result = new int[tam1 + tam2];
	
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


	return result;
}

int* merge_sort(int a[], int tam){
	if(tam<=1){
		int *d = new int;
		*d = a[0];
		return d;
	}
	int *b;
	b = merge_sort(a, tam/2);
	int *c;
	c = merge_sort(&a[tam/2], tam - tam/2);

	int *m = merge(b, c, tam/2, tam-tam/2);

	delete[] b;
	delete[] c;

	return m;
}

int* insertion_sort(int a[], int tam){
	
}

bool is_sorted(int a[], int tam){
	for(int i=0; i<tam-1; i++){
		if(a[i]>a[i+1]){
			return false;
		}
	}
	return true;
}


int main(){

	int testes[10];

	for(int i=1; i<=10; i++){
		testes[i-1]=10000*i;
	}

	for(int i=0; i<10; i++){
		srand(1024);

		# call insert_sort and  calculate the time
		start = time.time()
		sorted_a = insert_sort(b)
		if not is_sorted(sorted_a):
			print("ERROR1")
		end = time.time()
		t1 = end-start

		# call merge_sort and  calculate the time
		start = time.time()
		sorted_a = merge_sort(a)
		if not is_sorted(sorted_a):
			print("ERROR2")
		end = time.time()
		t2 = end-start

		print("%d %f %f" % (n, t1, t2))
	}
	int a[]={1,2,5,7,9,4,2,5,8,9,5};

	int *result;

	result = merge_sort(a,10);

	print(result,10);

}
