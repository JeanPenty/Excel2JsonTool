//stamp:076a8aa3c8ebaa81
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
			}
			const TCHAR * XML_MAINWND;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _PNG{
			public:
			_PNG(){
				IDB_PNG_SHADOW = _T("PNG:IDB_PNG_SHADOW");
				IDB_PNG_SHADOW2 = _T("PNG:IDB_PNG_SHADOW2");
				IDB_PNG_BTNMIN = _T("PNG:IDB_PNG_BTNMIN");
				IDB_PNG_BTNMAX = _T("PNG:IDB_PNG_BTNMAX");
				IDB_PNG_BTNRESTORE = _T("PNG:IDB_PNG_BTNRESTORE");
				IDB_PNG_BTNCLOSE = _T("PNG:IDB_PNG_BTNCLOSE");
				IDB_PNG_BTNSKIN = _T("PNG:IDB_PNG_BTNSKIN");
				IDB_BTN_COMM60_30 = _T("PNG:IDB_BTN_COMM60_30");
				IDB_PNG_CBXBTN = _T("PNG:IDB_PNG_CBXBTN");
				IDB_PNG_SB = _T("PNG:IDB_PNG_SB");
			}
			const TCHAR * IDB_PNG_SHADOW;
			const TCHAR * IDB_PNG_SHADOW2;
			const TCHAR * IDB_PNG_BTNMIN;
			const TCHAR * IDB_PNG_BTNMAX;
			const TCHAR * IDB_PNG_BTNRESTORE;
			const TCHAR * IDB_PNG_BTNCLOSE;
			const TCHAR * IDB_PNG_BTNSKIN;
			const TCHAR * IDB_BTN_COMM60_30;
			const TCHAR * IDB_PNG_CBXBTN;
			const TCHAR * IDB_PNG_SB;
		}PNG;
		class _IMG{
			public:
			_IMG(){
			}
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _translator{
			public:
			_translator(){
				lang_cn = _T("translator:lang_cn");
				lang_jp = _T("translator:lang_jp");
			}
			const TCHAR * lang_cn;
			const TCHAR * lang_jp;
		}translator;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"btn_array",65541},
		{L"btn_close",65536},
		{L"btn_max",65537},
		{L"btn_min",65539},
		{L"btn_obj",65542},
		{L"btn_restore",65538},
		{L"btn_root",65540},
		{L"btn_subobj",65543},
		{L"containerbox",65545},
		{L"scrollview",65544}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			btn_array = namedXmlID[1].strName;
			btn_close = namedXmlID[2].strName;
			btn_max = namedXmlID[3].strName;
			btn_min = namedXmlID[4].strName;
			btn_obj = namedXmlID[5].strName;
			btn_restore = namedXmlID[6].strName;
			btn_root = namedXmlID[7].strName;
			btn_subobj = namedXmlID[8].strName;
			containerbox = namedXmlID[9].strName;
			scrollview = namedXmlID[10].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * btn_array;
		 const wchar_t * btn_close;
		 const wchar_t * btn_max;
		 const wchar_t * btn_min;
		 const wchar_t * btn_obj;
		 const wchar_t * btn_restore;
		 const wchar_t * btn_root;
		 const wchar_t * btn_subobj;
		 const wchar_t * containerbox;
		 const wchar_t * scrollview;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int btn_array	=	65541;
		const static int btn_close	=	65536;
		const static int btn_max	=	65537;
		const static int btn_min	=	65539;
		const static int btn_obj	=	65542;
		const static int btn_restore	=	65538;
		const static int btn_root	=	65540;
		const static int btn_subobj	=	65543;
		const static int containerbox	=	65545;
		const static int scrollview	=	65544;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
