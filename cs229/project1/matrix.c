#include <stdio.h>
#include "MatrixMultiplier.h"
#include <jni.h>

JNIEXPORT void JNICALL Java_MatrixMultiplier_matrix (JNIEnv *env, jobject obj, jobjectArray a, jobjectArray b, jobjectArray r) {
	int result[3][3];
	int i, j, k;
	jintArray row, acrossJint, downJint;
	jint *across;
	jint *down;

	for(i = 0; i < 3; i++) {
		/* retrieve the row */
		acrossJint = (jintArray) (*env)->GetObjectArrayElement(env, a, i);
		across = (jint *) (*env)->GetIntArrayElements(env, acrossJint, 0);

		for(j = 0; j < 3; j++) {
			/* make sure it's zero */
			result[i][j] = 0;

			for(k = 0; k < 3; k++) {
				/* get the jint array like before */
				downJint = (jintArray) (*env)->GetObjectArrayElement(env, b, k);
				down = (jint *) (*env)->GetIntArrayElements(env, downJint, 0);

				/* store the result */
				result[i][j] += across[k] * down[j];
			}
		}

		/* we need to set the return matrix using these functions */
		row = (jintArray) (*env)->NewIntArray(env, 3);
		
		/* and we're done */
		(*env)->SetIntArrayRegion(env, row, 0, 3, (jint *) result[i]);
		(*env)->SetObjectArrayElement(env, r, i, row);
	}
}
