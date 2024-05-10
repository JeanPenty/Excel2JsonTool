#pragma once

//原则：>=0表示成功 <0表示失败
#define JP_OK 0
//判断当前值是否为“失败”
#define JP_FAILED( jpResult ) ( jpResult != JP_OK )

//判断当前值是否为“成功”
#define JP_SUCCEEDED( jpResult ) ( jpResult == JP_OK )

