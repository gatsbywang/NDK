//ʵ�����ǵ�native����
#include "com_demo_ndk_NdkSimple.h"
#include "com_demo_ndk_NdkSimple2.h"

//JNIEXPORT JNIһ���ؼ��֣������٣�������ͨ��������Ǹ÷������Ա��ⲿ����
//jstring ����java�е�String
//JNICALL Ҳ��һ���ؼ��֣������ٵģ�����jni����
//JNIEnv  ���c ��java �໥���õ�����  
//jobject java���������Ķ��󣬾��Ǳ���Ŀ�д��ݵ�java���󣬾���JniSimple
//jclass: java����������class���󣬾��Ǳ���Ŀ�е�JniSimple.class
JNIEXPORT jstring JNICALL Java_com_demo_ndk_NdkSimple_getStringnaturePassword
(JNIEnv *env, jobject jobject) {
	//JNIEnv * ��һ������ָ�룬��->�� ֻ����һ��ָ����ܵ���
	return (*env)->NewStringUTF(env, "940223");
}


JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_changeName
(JNIEnv *env, jobject jobj) {
	
	//3����ȡjclass
	jclass j_clz = (*env)->GetObjectClass(env,jobj);

	//name ��ȡ�ĸ����Ե�����
	//2��sig ���Ե�ǩ�� ǩ������Ҫ��ס����ͨ��javap -p -s ���� ���Ի�ȡ
	jfieldID j_fid = (*env)->GetFieldID(env, j_clz,"name","Ljava/lang/String;");
	//1����ȡname ����
	jstring j_str = (*env)->GetObjectField(env,jobj, j_fid);

	//��ӡ�ַ��� jstring-> c_str
	char *c_str = (*env)->GetStringUTFChars(env,j_str,NULL);

	printf("name is %s",c_str);

	//�޸ĳ� ������
	jstring name = (*env)->NewStringUTF(env,"������");
	(*env)->SetObjectField(env,jobj,j_fid, name);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_changeAge
(JNIEnv *env, jclass jcls) {
	//�޸�static ����


	//2����ȡjfiledid
	jfieldID f_fid = (*env)->GetStaticFieldID(env, jcls,"age","I");
	//1����ȡ��̬������
	jint old_age = (*env)->GetStaticIntField(env, jcls, f_fid);

	old_age += 12;

	//�����µ�age����
	(*env)->SetStaticIntField(env,jcls,f_fid,old_age);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_callAddMethod
(JNIEnv *env, jobject jobj) {



	//����java����

	//3����ȡjclass
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//2����ȡjmethodId
	jmethodID j_mid = (*env)->GetMethodID(env, j_clz, "add", "(II)I");

	//1������add����
	jint sum = (*env)->CallIntMethod(env,jobj, j_mid,2,3);

	printf("sum is %d", sum);
}
