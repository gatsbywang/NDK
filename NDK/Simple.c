//实现我们的native方法
#include "com_demo_ndk_NdkSimple.h"
#include "com_demo_ndk_NdkSimple2.h"
#include "com_demo_ndk_NdkSimple3.h"

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
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//name 获取哪个属性的属性
	//2、sig 属性的签名 签名不需要记住规则，通过javap -p -s 类名 可以获取
	jfieldID j_fid = (*env)->GetFieldID(env, j_clz, "name", "Ljava/lang/String;");
	//1、获取name 属性
	jstring j_str = (*env)->GetObjectField(env, jobj, j_fid);

	//打印字符串 jstring-> c_str
	char *c_str = (*env)->GetStringUTFChars(env, j_str, NULL);

	printf("name is %s", c_str);

	//修改成 花歹歹
	jstring name = (*env)->NewStringUTF(env, "花歹歹");
	(*env)->SetObjectField(env, jobj, j_fid, name);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_changeAge
(JNIEnv *env, jclass jcls) {
	//修改static 变量


	//2、获取jfiledid
	jfieldID f_fid = (*env)->GetStaticFieldID(env, jcls, "age", "I");
	//1、获取静态的属性
	jint old_age = (*env)->GetStaticIntField(env, jcls, f_fid);

	old_age += 12;

	//设置新的age参数
	(*env)->SetStaticIntField(env, jcls, f_fid, old_age);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple2_callAddMethod
(JNIEnv *env, jobject jobj) {



	//调用java方法

	//3、获取jclass
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//2、获取jmethodId
	jmethodID j_mid = (*env)->GetMethodID(env, j_clz, "add", "(II)I");

	//1、调用add方法
	jint sum = (*env)->CallIntMethod(env, jobj, j_mid, 2, 3);

	printf("sum is %d", sum);
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple3_callStaticMethod
(JNIEnv *env, jclass jcls) {

	//2、获取methodId 这次需要记住了方法签名
	jmethodID j_mid = (*env)->GetStaticMethodID(env, jcls, "getUUID", "()Ljava/lang/String;");
	//1、调用UUID的方法
	jstring j_uuid = (*env)->CallStaticObjectMethod(env, jcls, j_mid);

	char* c_uuid = (*env)->GetStringUTFChars(env, j_uuid, NULL);

	//回收
	(*env)->ReleaseStringUTFChars(env, j_uuid, c_uuid);
	printf("c_uuid = %s", c_uuid);
}

JNIEXPORT jobject JNICALL Java_com_demo_ndk_NdkSimple3_createPoint
(JNIEnv *env, jclass jcls) {
	

	// 获取Point 的class
	jclass point_cls = (*env)->FindClass(env,"com/demo/ndk/Point");
	// 构造方法 的方法名和方法签名得注意
	jmethodID j_mid = (*env)->GetMethodID(env, point_cls, "<init>", "(II)V");
	//构建 java层的Point对象
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
	//常量指针
	const int *n_p = &number2;
	n_p = &number1;
	printf("n_p =%p",n_p);
	//*n_p = 300; 值不能被修改
	
	//指针常量
	int * const p_n = &number2;
	//p_n = &number1;地址不能被修改
	*p_n = 300;
}*/


