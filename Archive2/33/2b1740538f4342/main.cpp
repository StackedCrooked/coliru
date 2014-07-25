int arr[10];

int& get(int idx){
    return arr[idx];  
}

int& get2(int idx){
    return get(idx);
}

int main() {}