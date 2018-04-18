/*
typedef const struct JNINativeInterface *JNIEnv;

struct JNINativeInterface {
	//结构体的方法指针

	char *(*NewStringUTF)(JNIEnv *env, char* c_str);

};

char * NewStringUTF(JNIEnv *env, char* c_str) {

	return c_str;
}

 char* Java_com_demo_ndk_NdkSimple_getStringnaturePassword
(JNIEnv *env) {
	//JNIEnv * 是一个二级指针，“->” 只有在一级指针才能调用
	return (*env)->NewStringUTF(env, "940223");
	
}

void main() {
	//构建 JNIEnv* 对象
	JNINativeInterface nativeInterface;
	//给结构体中的方法指针进行实现
	nativeInterface.NewStringUTF = NewStringUTF;

	//

	JNIEnv env = &nativeInterface; //一级指针

	JNIEnv *jniEnv = &env; //二级指针

	char * jstring = Java_com_demo_ndk_NdkSimple_getStringnaturePassword(jniEnv);
	//getchar();
}*/