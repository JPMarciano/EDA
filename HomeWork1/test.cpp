#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

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
	int cv;
	int j;
	for(int i=0; i<tam;i++){
        cv = a[i];
        j = i-1;
        while(j >= 0 && a[j] > cv){
            a[j+1] = a[j];
            j = j - 1;
        }
        a[j+1] = cv;
	}
    return a;
}

bool is_sorted(int a[], int tam){
	for(int i=0; i<tam-1; i++){
		if(a[i]>a[i+1]){
			return false;
		}
	}
	return true;
}
struct timespec tsbegin, tsend;

void begin()
{
	clock_gettime(CLOCK_MONOTONIC, &tsbegin);
}

float end()
{
	clock_gettime(CLOCK_MONOTONIC, &tsend);
	return (tsend.tv_sec - tsbegin.tv_sec) + (tsend.tv_nsec - tsbegin.tv_nsec) / (1E9);
}


int main(){

	int testes[10];
	
	float t1,t2;
	
	for(int i=1; i<=10; i++){
		testes[i-1]=10000*i;
	}
	
	for(int i=0; i<10; i++){
		srand(1024);
		
		int *a = new int[testes[i]];
		
		int *sorted_c, *sorted_b;
		
		int b[testes[i]];
		int c[testes[i]];
		
		for(int j =0; j<testes[i]; j++){
			a[j] = rand();
		}
		
		//copy a into b and c
		for(int i =0; i<testes[i]; i++){
			b[i] = a[i];
			c[i] = a[i];
		}

		
		// call insert_sort and  calculate the time for a random array
		begin();
		sorted_b = insertion_sort(b, testes[i]);
		t1 = end();
		
		if (!(is_sorted(sorted_b, testes[i]))){
			std::cout << "ERROR1";
		}
		
		// call merge_sort and  calculate the time for a random array
		begin();
		sorted_c = merge_sort(c, testes[i]);
		t2 = end();
		if (!(is_sorted(sorted_c, testes[i]))){
			std::cout << "ERROR2";
		}

		std::cout << "Random, " << testes[i] << ", " << t1 << ", " << t2 << std::endl;

		// call insert_sort and  calculate the time for an ascending array
		begin();
		sorted_b = insertion_sort(sorted_b, testes[i]);
		t1 = end();
		
		if (!(is_sorted(sorted_b, testes[i]))){
			std::cout << "ERROR1";
		}
		
		// call merge_sort and  calculate the time for an ascending array
		begin();
		sorted_c = merge_sort(sorted_c, testes[i]);
		t2 = end();
		if (!(is_sorted(sorted_c, testes[i]))){
			std::cout << "ERROR2";
		}

		std::cout << "Ascending, " << testes[i] << ", " << t1 << ", " << t2 << std::endl;

		// reverse
		for(int j = 0; j<testes[i]; j++){
			b[j] = sorted_b[testes[i]-j-1];
			c[j] = sorted_b[testes[i]-j-1];
		}

		// call insert_sort and  calculate the time for a descending array
		begin();
		sorted_b = insertion_sort(b, testes[i]);
		t1 = end();
		
		if (!(is_sorted(sorted_b, testes[i]))){
			std::cout << "ERROR1";
		}
		
		// call merge_sort and  calculate the time for a descending array
		begin();
		sorted_c = merge_sort(c, testes[i]);
		t2 = end();
		if (!(is_sorted(sorted_c, testes[i]))){
			std::cout << "ERROR2";
		}

		std::cout << "Descending, " << testes[i] << ", " << t1 << ", " << t2 << std::endl;
	}
}
