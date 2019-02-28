#include <stdio.h>

//메모리 관련 커널은 mm_struct에 있다.
//vm_area_struct :가상메모리 영역 관리 구조체
//mm_struct 내부에 rb_tree가 있는 이유는 특정 규칭(사용 빈도 수)에 따라 process를 검색하기 위해서이다.
//가상 메모리 공간은 7개의 usigned long 변수로 표현된다.
//각 프로세서의 부여된 가상메모리 공간은 독립적이다. 
// 그러므로 다른 프로세서가 또 다른 프로세서의 공간을 정상적인 방법으로 참조 및 변경시킬 수 없다.
int main(void)
{
	int *p = 0x7ffc614bed94;
	printf("a = %d=n",*p);

	return 0;
}
