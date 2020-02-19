#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

//��ҳ��ͳһ����
class QtATM;
class GuidePage;
class JoinPage;
class LoginPage;
class NUserPage;
class HUserPage;

extern QtATM* qtATM;
extern GuidePage* guidePage;
extern JoinPage* joinPage;
extern LoginPage* loginPage;
extern NUserPage* nUserPage;
extern HUserPage* hUserPage;

//��¼����ҳ��
extern int topPage;

const static int PAGE_QTATM = 0;
const static int PAGE_GUIDE = 1;
const static int PAGE_JOIN = 2;
const static int PAGE_LOGIN = 3;
const static int PAGE_NUSER = 4;
const static int PAGE_HUSER = 5;

#endif;