#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>

__global__ void addKernel(int* c, const int* a, const int* b)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

extern "C" void runCuda()
{
    const int size = 5;
    int a[size] = { 1, 2, 3, 4, 5 };
    int b[size] = { 10, 20, 30, 40, 50 };
    int c[size] = { 0 };

    int* dev_a = nullptr;
    int* dev_b = nullptr;
    int* dev_c = nullptr;

    cudaMalloc((void**)&dev_a, size * sizeof(int));
    cudaMalloc((void**)&dev_b, size * sizeof(int));
    cudaMalloc((void**)&dev_c, size * sizeof(int));

    cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);

    addKernel << <1, size >> > (dev_c, dev_a, dev_b);

    cudaDeviceSynchronize();

    cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < size; ++i)
        printf("%d + %d = %d\n", a[i], b[i], c[i]);

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}