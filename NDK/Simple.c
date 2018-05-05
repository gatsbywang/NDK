//实现我们的native方法
#include "com_demo_ndk_NdkSimple.h"
#include "com_demo_ndk_NdkSimple2.h"
#include "com_demo_ndk_NdkSimple3.h"
#include "com_demo_ndk_NdkSimple4.h"
#include <stdlib.h>

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
	jclass point_cls = (*env)->FindClass(env, "com/demo/ndk/Point");
	// 构造方法 的方法名和方法签名得注意
	jmethodID j_mid = (*env)->GetMethodID(env, point_cls, "<init>", "(II)V");
	//构建 java层的Point对象
	jobject point = (*env)->NewObject(env, point_cls, j_mid, 11, 22);

	jmethodID setX_mid = (*env)->GetMethodID(env, point_cls, "setX", "(I)V");
	/*void (JNICALL *CallVoidMethodV)
		(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
	void (JNICALL *CallVoidMethodA)
		(JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);*/
	(*env)->CallVoidMethod(env, point, setX_mid, 33);
	return point;
}

int compare(const jint *number1, const jint *number2) {
	return *number1 - *number2;
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_sort
(JNIEnv *env, jclass jcls, jintArray jarray) {

	jint* intArray = (*env)->GetIntArrayElements(env, jarray, NULL);

	int length = (*env)->GetArrayLength(env, jarray);
	//第一个参数：void* 数组的首地址
	//第二个参数：数组的大小长度
	//第三个参数：数组元素数据类型的大小
	//第四个参数：数组的一个比较方法指针（Comparable）
	qsort(intArray, length, sizeof(int), compare);

	//同步数组的数据给java数组
	//0：既要同步数组给jarray,又要释放jni*
	//JNI_COMMOT:同步数据给jarray,但不会释放jniArray
	//JNI_ABORT：不同步数据给jarray,但会释放jniArray
	(*env)->ReleaseIntArrayElements(env, jarray, intArray, 0);

}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_localRef
(JNIEnv *env, jclass jcls) {

	// 在native层构建的java对象，你不用了怎么管理？
	// native层开辟的内存由谁管理，能开辟多大？

	//字符串截取，String对象
	(*env)->FindClass();
	(*env)->NewObject();

	//删除了就不能再使用了，C和C++ 都需要自己释放内存（静态开辟的不需要，动态开辟的需要）
	(*env)->DeleteLocalRef();
	(*env)->release
}

jstring globalStr;
JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_saveGlobalRef
(JNIEnv *env, jclass jcls, jstring jstring) {
	//全局变量
	globalStr = (*env)->NewGlobalRef(env,jstring);
	//弱引用全局变量跟java的软引用很像，无法保证对象不为空。 
	(*env)->NewWeakGlobalRef(env, jstring);
}

JNIEXPORT jstring JNICALL Java_com_demo_ndk_NdkSimple4_getGlobalRef
(JNIEnv *env, jclass jcls) {
	//返回全局引用
	return globalStr;
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_deleteGlobalRef
(JNIEnv *env, jclass jcls, jstring jstring) {
	//删除全局引用
	(*env)->DeleteGlobalRef(env, jstring);
}


JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_staticLocalCache
(JNIEnv *env, jclass jcls, jstring name) {
	/*static jfieldID f_id = NULL; //局部缓存，这方法会被多次调用，不会反复去获取jfieldID 
	if (f_id == NULL) {
		f_id = (*env)->GetStaticFieldID(env, jcls, "name", "Ljava/lang/String;");
	}
	else {
		//方法多次调用 只会进到这里，这就是局部缓存作用
		printf("f_id 不为 null");
	}
	(*env)->SetStaticObjectField(env,jcls, f_id,name);*/

	(*env)->SetStaticObjectField(env, jcls, f_name_id, name);
}

//全局静态缓存,在构造函数(java的构造函数)中初始化的会去缓存
static jfieldID f_name_id = NULL;
static jfieldID f_name1_id = NULL;
static jfieldID f_name2_id = NULL;

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_initStaticCache
(JNIEnv *env, jclass jcls) {
	f_name_id  = (*env)->GetStaticFieldID(env, jcls, "name", "Ljava/lang/String;");
	f_name1_id = (*env)->GetStaticFieldID(env, jcls, "name1", "Ljava/lang/String;");
	f_name2_id = (*env)->GetStaticFieldID(env, jcls, "name2", "Ljava/lang/String;");
}

JNIEXPORT void JNICALL Java_com_demo_ndk_NdkSimple4_exception
(JNIEnv *env, jclass jcls){

	//假设赋值给name3,name3在java中不存在的
	jfieldID f_id = (*env)->GetStaticFieldID(env, jcls, "name3", "Ljava/lang/String;");

	jthrowable throwable = (*env)->ExceptionOccurred(env);
	if (throwable) {

		printf("有异常");
		//清除异常
		(*env)->ExceptionClear(env);

		//想给java层抛一个异常
		jclass no_such_field = (*env)->FindClass(env,"java/lang/NoSuchFieldException");
		(*env)->ThrowNew(env,no_such_field, "no_such_field");
;
		//补救措施
		f_id = (*env)->GetStaticFieldID(env, jcls, "name", "Ljava/lang/String;");
	}
	jstring name = (*env)->NewStringUTF(env,"langligelang");
	(*env)->SetStaticObjectField(env, jcls, f_name_id, name);
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


