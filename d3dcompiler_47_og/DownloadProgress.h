#ifndef DOWNLOADPROGRESS_H
#define DOWNLOADPROGRESS_H
#pragma comment(lib, "urlmon.lib")
#pragma once

#include <windows.h>
#include <iostream>

namespace moddingApi
{
    class DownloadProgress : public IBindStatusCallback
    {
    public:
        float progress;
        float GetProgress();
        HRESULT __stdcall QueryInterface(const IID&, void**);
        ULONG STDMETHODCALLTYPE AddRef(void);
        ULONG STDMETHODCALLTYPE Release(void);
        HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib);
        virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG* pnPriority);
        virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved);
        virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError);
        virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo);
        virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed);
        virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk);
        virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText);
    };
}

#endif