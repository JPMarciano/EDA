#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std::chrono;

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


int main(){

	int testes[10];
	
	int t1,t2;
	
	time_point<system_clock> start, end;
	
	for(int i=1; i<=10; i++){
		testes[i-1]=10000*i;
	}
	
	testes[0]=50;
	
	for(int i=0; i<10; i++){
		srand(1024);
		
		int a[testes[i]];
		
		int *sorted_a;
		
		int b[testes[i]];
		
		for(int j =0; j<testes[i]; j++){
			a[j] = rand();
		}
		
		memcpy(b, a, testes[i]*sizeof(int));
		
		// call insert_sort and  calculate the time
		start = system_clock::now();
		sorted_a = insertion_sort(b, testes[i]);
		end = system_clock::now();
		if (!(is_sorted(sorted_a, testes[i]))){
			std::cout << "ERROR1";
		}
		t1 = duration_cast<seconds> (end-start).count();
		// call merge_sort and  calculate the time
		sorted_a = merge_sort(a, testes[i]);
		if (!(is_sorted(sorted_a, testes[i]))){
			std::cout << "ERROR2";
		}

		//print("%d %f %f" % (n, t1, t2))
	}
}
