/*
typedef const struct JNINativeInterface *JNIEnv;

struct JNINativeInterface {
	//�ṹ��ķ���ָ��

	char *(*NewStringUTF)(JNIEnv *env, char* c_str);

};

char * NewStringUTF(JNIEnv *env, char* c_str) {

	return c_str;
}

 char* Java_com_demo_ndk_NdkSimple_getStringnaturePassword
(JNIEnv *env) {
	//JNIEnv * ��һ������ָ�룬��->�� ֻ����һ��ָ����ܵ���
	return (*env)->NewStringUTF(env, "940223");
	
}

void main() {
	//���� JNIEnv* ����
	JNINativeInterface nativeInterface;
	//���ṹ���еķ���ָ�����ʵ��
	nativeInterface.NewStringUTF = NewStringUTF;

	//

	JNIEnv env = &nativeInterface; //һ��ָ��

	JNIEnv *jniEnv = &env; //����ָ��

	char * jstring = Java_com_demo_ndk_NdkSimple_getStringnaturePassword(jniEnv);
	//getchar();
}*/