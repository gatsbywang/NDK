//ʵ�����ǵ�native����
#include "com_demo_ndk_NdkSimple.h"
#include "com_demo_ndk_NdkSimple2.h"
#include "com_demo_ndk_NdkSimple3.h"

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
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//name ��ȡ�ĸ����Ե�����
	//2��sig ���Ե�ǩ�� ǩ������Ҫ��ס����ͨ��javap -p -s ���� ���Ի�ȡ
	jfieldID j_fid = (*env)->GetFieldID(env, j_clz, "name", "Ljava/lang/String;");
	//1����ȡname ����
	jstring j_str = (*env)->GetObjectField(env, jobj, j_fid);

	//��ӡ�ַ��� jstring-> c_str
	char *c_str = (*env)->GetStringUTFChars(env, j_str, NULL);

	printf("name is %s", c_str);

	//�޸ĳ� ������
	jstring name = (*env)->NewStringUTF(env, "������");
	(*env)->SetObjectField(env, jobj, j_fid, name);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_changeAge
(JNIEnv *env, jclass jcls) {
	//�޸�static ����


	//2����ȡjfiledid
	jfieldID f_fid = (*env)->GetStaticFieldID(env, jcls, "age", "I");
	//1����ȡ��̬������
	jint old_age = (*env)->GetStaticIntField(env, jcls, f_fid);

	old_age += 12;

	//�����µ�age����
	(*env)->SetStaticIntField(env, jcls, f_fid, old_age);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_callAddMethod
(JNIEnv *env, jobject jobj) {



	//����java����

	//3����ȡjclass
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//2����ȡjmethodId
	jmethodID j_mid = (*env)->GetMethodID(env, j_clz, "add", "(II)I");

	//1������add����
	jint sum = (*env)->CallIntMethod(env, jobj, j_mid, 2, 3);

	printf("sum is %d", sum);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple3_callStaticMethod
(JNIEnv *env, jclass jcls) {

	//2����ȡmethodId �����Ҫ��ס�˷���ǩ��
	jmethodID j_mid = (*env)->GetStaticMethodID(env, jcls, "getUUID", "()Ljava/lang/String;");
	//1������UUID�ķ���
	jstring j_uuid = (*env)->CallStaticObjectMethod(env, jcls, j_mid);

	char* c_uuid = (*env)->GetStringUTFChars(env, j_uuid, NULL);

	//����
	(*env)->ReleaseStringUTFChars(env, j_uuid, c_uuid);
	printf("c_uuid = %s", c_uuid);
}

JNIEXPORT jobject JNICALL Java_com_demo_ndk_NdkSimple3_createPoint
(JNIEnv *env, jclass jcls) {
	

	// ��ȡPoint ��class
	jclass point_cls = (*env)->FindClass(env,"com/demo/ndk/Point");
	// ���췽�� �ķ������ͷ���ǩ����ע��
	jmethodID j_mid = (*env)->GetMethodID(env, point_cls, "<init>", "(II)V");
	//���� java���Point����
	jobject point = (*env)->NewObject(env, point_cls, j_mid,11,22);

	jmethodID setX_mid = (*env)->GetMethodID(env, point_cls, "setX", "(I)V");
	/*void (JNICALL *CallVoidMethodV)
		(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
	void (JNICALL *CallVoidMethodA)
		(JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);*/
	(*env)->CallVoidMethod(env,point, setX_mid,33);
	return point;
}

/*void main() {
	const int number = 100;

	int number1 = 100;
	int number2 = 200;
	//����ָ��
	const int *n_p = &number2;
	n_p = &number1;
	printf("n_p =%p",n_p);
	//*n_p = 300; ֵ���ܱ��޸�
	
	//ָ�볣��
	int * const p_n = &number2;
	//p_n = &number1;��ַ���ܱ��޸�
	*p_n = 300;
}*/


