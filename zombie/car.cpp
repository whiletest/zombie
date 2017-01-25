#include "stdafx.h"

CCar::CCar(int id /* = 0 */,
		   int iWidth /* = 0 */,
		   int iHeight /* = 0 */
		   ):CSceneObject(id,iWidth,iHeight),
		   m_ikey(0)
{

}

CCar::~CCar()
{

}

BOOL CCar::Open(int iKey)
{
	if (m_ikey == 0) //没有钥匙不能打开
		return FALSE;
	if (iKey == m_ikey)
		return TRUE;
	return FALSE;
}