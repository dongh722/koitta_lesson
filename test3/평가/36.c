Blocking 연산의 경우 system call을 요청했을 때 그 task가 요청에 대한 회신을 받을 때 까지 아무 일도 못하고 대기하고 있다.
Non_blocking의 경우 system call을 요청했을 회신을 대기하지 않고 회신 할때 까지 다른 작업을 하고 있는 것이다.
