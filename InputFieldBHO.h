

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Dec 13 23:16:51 2018
 */
/* Compiler settings for InputFieldBHO.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __InputFieldBHO_h__
#define __InputFieldBHO_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInputFieldBHO2_FWD_DEFINED__
#define __IInputFieldBHO2_FWD_DEFINED__
typedef interface IInputFieldBHO2 IInputFieldBHO2;

#endif 	/* __IInputFieldBHO2_FWD_DEFINED__ */


#ifndef __InputFieldBHO2_FWD_DEFINED__
#define __InputFieldBHO2_FWD_DEFINED__

#ifdef __cplusplus
typedef class InputFieldBHO2 InputFieldBHO2;
#else
typedef struct InputFieldBHO2 InputFieldBHO2;
#endif /* __cplusplus */

#endif 	/* __InputFieldBHO2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IInputFieldBHO2_INTERFACE_DEFINED__
#define __IInputFieldBHO2_INTERFACE_DEFINED__

/* interface IInputFieldBHO2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInputFieldBHO2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C946A777-DDF6-4031-8D79-3F6A5CFC4048")
    IInputFieldBHO2 : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IInputFieldBHO2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInputFieldBHO2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInputFieldBHO2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInputFieldBHO2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInputFieldBHO2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInputFieldBHO2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInputFieldBHO2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInputFieldBHO2 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IInputFieldBHO2Vtbl;

    interface IInputFieldBHO2
    {
        CONST_VTBL struct IInputFieldBHO2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInputFieldBHO2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInputFieldBHO2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInputFieldBHO2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInputFieldBHO2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IInputFieldBHO2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IInputFieldBHO2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IInputFieldBHO2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInputFieldBHO2_INTERFACE_DEFINED__ */



#ifndef __InputFieldBHOLib_LIBRARY_DEFINED__
#define __InputFieldBHOLib_LIBRARY_DEFINED__

/* library InputFieldBHOLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_InputFieldBHOLib;

EXTERN_C const CLSID CLSID_InputFieldBHO2;

#ifdef __cplusplus

class DECLSPEC_UUID("256B37DB-CAF4-4190-8178-787427B9028A")
InputFieldBHO2;
#endif
#endif /* __InputFieldBHOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


