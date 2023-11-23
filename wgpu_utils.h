#ifndef WGPU_UTILS_H
#define WGPU_UTILS_H

#include "webgpu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WGPU {
    WGPUInstance instance; // navigator.gpu
    WGPUAdapter adapter; // navigator.gpu.requestAdapter()
    WGPUSurface surface; // canvas.getContext('gpupresent')
    WGPUDevice device; // adapter.requestDevice()
    WGPUQueue queue; // device.getQueue()
} WGPU;

// https://eliemichel.github.io/LearnWebGPU/getting-started/the-adapter.html
WGPUAdapter wgpuRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const * options);

// https://eliemichel.github.io/LearnWebGPU/getting-started/the-device.html
WGPUDevice wgpuRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor);

WGPU wgpuInit(WGPUInstance instance, WGPUSurface surface, WGPURequestAdapterOptions * options, WGPUDeviceDescriptor * descriptor);


#ifdef __cplusplus
}
#endif

#endif
