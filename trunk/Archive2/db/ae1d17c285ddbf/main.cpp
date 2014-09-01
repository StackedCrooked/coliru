struct handle {
  int hhh;
};

void elaborateHandle(handle h);

int main() {
  handle h = {3};

  elaborateHandle(h);
}
