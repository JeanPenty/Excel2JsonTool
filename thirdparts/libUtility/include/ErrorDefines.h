#pragma once

//ԭ��>=0��ʾ�ɹ� <0��ʾʧ��
#define JP_OK 0
//�жϵ�ǰֵ�Ƿ�Ϊ��ʧ�ܡ�
#define JP_FAILED( jpResult ) ( jpResult != JP_OK )

//�жϵ�ǰֵ�Ƿ�Ϊ���ɹ���
#define JP_SUCCEEDED( jpResult ) ( jpResult == JP_OK )

