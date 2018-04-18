//实现我们的native方法
#include "com_demo_ndk_NdkSimple.h"
#include "com_demo_ndk_NdkSimple2.h"

//JNIEXPORT JNI一个关键字，不能少（编译能通过），标记该方法可以被外部调用
//jstring 代表java中的String
//JNICALL 也是一个关键字，可以少的，代表jni调用
//JNIEnv  这个c 和java 相互调用的桥梁  
//jobject java传递下来的对象，就是本项目中传递的java对象，就是JniSimple
//jclass: java传递下来的class对象，就是本项目中的JniSimple.class
JNIEXPORT jstring JNICALL Java_com_demo_ndk_NdkSimple_getStringnaturePassword
(JNIEnv *env, jobject jobject) {
	//JNIEnv * 是一个二级指针，“->” 只有在一级指针才能调用
	return (*env)->NewStringUTF(env, "940223");
}


JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_changeName
(JNIEnv *env, jobject jobj) {
	
	//3、获取jclass
	jclass j_clz = (*env)->GetObjectClass(env,jobj);

	//name 获取哪个属性的属性
	//2、sig 属性的签名 签名不需要记住规则，通过javap -p -s 类名 可以获取
	jfieldID j_fid = (*env)->GetFieldID(env, j_clz,"name","Ljava/lang/String;");
	//1、获取name 属性
	jstring j_str = (*env)->GetObjectField(env,jobj, j_fid);

	//打印字符串 jstring-> c_str
	char *c_str = (*env)->GetStringUTFChars(env,j_str,NULL);

	printf("name is %s",c_str);

	//修改成 花歹歹
	jstring name = (*env)->NewStringUTF(env,"花歹歹");
	(*env)->SetObjectField(env,jobj,j_fid, name);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_changeAge
(JNIEnv *env, jclass jcls) {
	//修改static 变量


	//2、获取jfiledid
	jfieldID f_fid = (*env)->GetStaticFieldID(env, jcls,"age","I");
	//1、获取静态的属性
	jint old_age = (*env)->GetStaticIntField(env, jcls, f_fid);

	old_age += 12;

	//设置新的age参数
	(*env)->SetStaticIntField(env,jcls,f_fid,old_age);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_callAddMethod
(JNIEnv *env, jobject jobj) {



	//调用java方法

	//3、获取jclass
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//2、获取jmethodId
	jmethodID j_mid = (*env)->GetMethodID(env, j_clz, "add", "(II)I");

	//1、调用add方法
	jint sum = (*env)->CallIntMethod(env,jobj, j_mid,2,3);

	printf("sum is %d", sum);
}
