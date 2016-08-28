# Minesweeper-solve-algorithm

Project : Minesweeper hack

평소에 지뢰 찾기하다가 문뜩 지뢰 찾기 핵만들어 보고싶은 마음이 들어서 무작정 시작한 프로젝트입니다.
협업 경험이 없는 학생이 짠 코드라서 정리가 약간 안되있을수 있습니다.
저의 잛디잛은 영어로 주석달아놔서 안 읽힐수도 있습니다.

Getting Started
----------------------------------------------------------------------------------------------------------------------------
1. 모든 파일들을 다운 받아주세요.
2. main.cpp를 컴파일 한 후 실행해 주시면 됨니다. (C++ 5.3.0 컴파일러 이상)

Files
----------------------------------------------------------------------------------------------------------------------------
main.cpp : main()
minesweeper.h : 지뢰 찾기 맵 생성 (Minesweeper_make_map)
player.h : 지뢰 찾기 알고리즘 (minesolve1, MSA)
zero.h : 글자색 바꾸기 (textcolor)

Algorithm
----------------------------------------------------------------------------------------------------------------------------
1. 숫자 세기, minesolve1
숫자 칸 주위에 오픈되지 않은 칸 수(B)와 깃발을 수(F), 숫자 칸 값(n), n==F이라면 주위 오픈되지 않은 블럭 모두 클릭. n-F==B이라면 오픈되지 않은 블럭 모두 깃발 마킹. 이 두 작업 중에 하나를 했다면 큐에서 삭제한다. 더 이상 큐에서 삭제할 칸이 없다면 두 번째 알고리즘으로 넘어간다.

2. Minesweeper Solve Algorithm, MSA
가상 플레이 서로 영향을 줄수 있는 칸들을 그룹화 시켜주기위해서 union find 알고리즘 응용(안해주면 시간이 곱으로 걸려서), 가능할수 있는 게임판을 만들기 위해 DFS를 이용했습니다. 가능할수 있는 게임판이 여러개가 나올겁니다. 하지만 그 중에 모든 경우에 무조건 폭탄인 칸이 있을 수 있고, 없을 수 있는 칸이 있습니다. 그런 칸들을 진행중인 게임판에 적용시켜줌니다.

3. 확률 게임
오픈되지 않은 칸 아무것나 찍어줌니다. 게임 오버나는 경우가 이 단계에서 폭탄을 찍어버리면 그렇습니다.
