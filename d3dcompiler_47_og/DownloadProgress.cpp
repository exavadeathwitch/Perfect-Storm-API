#include "DownloadProgress.h"
using namespace std;
using namespace moddingApi;

float progress;

HRESULT __stdcall DownloadProgress::QueryInterface(const IID&, void**) {
    return E_NOINTERFACE;
}
ULONG STDMETHODCALLTYPE DownloadProgress::AddRef(void) {
    return 1;
}
ULONG STDMETHODCALLTYPE DownloadProgress::Release(void) {
    return 1;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::OnStartBinding(DWORD dwReserved, IBinding* pib) {
    return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::GetPriority(LONG* pnPriority) {
    return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::OnLowResource(DWORD reserved) {
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::OnStopBinding(HRESULT hresult, LPCWSTR szError) {
    return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) {
    return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) {
    return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE DownloadProgress::OnObjectAvailable(REFIID riid, IUnknown* punk) {
    return E_NOTIMPL;
}

HRESULT __stdcall DownloadProgress::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
{
    wcout << ulProgress << L" of " << ulProgressMax;
    if (szStatusText) wcout << " " << szStatusText;
    progress = ulProgress / ulProgressMax;
    wcout << endl;
    return S_OK;
}

float GetProgress() {
    return progress;
}