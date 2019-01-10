int factorial(int x) {
  if (x <= 0) {
    return 0;
  } else {
    return x * factorial(x - 1);
  }
  // factorial is not so great
}
