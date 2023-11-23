#include "wgpu_utils.h"
#include <cassert>

WGPUAdapter wgpuRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const * options) {
    struct UserData {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const * message, void * pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestAdapterStatus_Success) {
            userData.adapter = adapter;
        } else {
            // TODO: handle error
        }
        userData.requestEnded = true;
    };

    wgpuInstanceRequestAdapter(
        instance, // navigator.gpu
        options,
        onAdapterRequestEnded,
        (void*)&userData
    );

    assert(userData.requestEnded);

    return userData.adapter;
}

WGPUDevice wgpuRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor) {
    struct UserData {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const * message, void * pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestDeviceStatus_Success) {
            userData.device = device;
        } else {
            // TODO: handle error
        }
        userData.requestEnded = true;
    };

    wgpuAdapterRequestDevice(
        adapter,
        descriptor,
        onDeviceRequestEnded,
        (void*)&userData
    );

    assert(userData.requestEnded);

    return userData.device;
}

WGPU wgpuInit(WGPUInstance instance, WGPUSurface surface, WGPURequestAdapterOptions * options, WGPUDeviceDescriptor * descriptor) {
    WGPU wgpu;
    wgpu.instance = instance;
    wgpu.surface = surface;

    options->compatibleSurface = surface;

    wgpu.adapter = wgpuRequestAdapter(instance, options);

    wgpu.device = wgpuRequestDevice(wgpu.adapter, descriptor);

    wgpu.queue = wgpuDeviceGetQueue(wgpu.device);

    return wgpu;
}