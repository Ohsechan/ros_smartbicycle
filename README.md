# Smart Bicycle
## 1. 프로젝트 소개
- 수상 경력
  - 2021 한이음 공모전 입선
- 설명
  - 자전거 운전자는 전방을 주시해야 하기 때문에, 측방 또는 후방에서 빠르게 다가오는 물체를 인지하는 것에 어려움이 있습니다.
  - 이 프로젝트에서는 운전자가 안전하게 운전할 수 있는 “스마트자전거”를 제작하였습니다.
- 사진
![bicycle](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/e127291b-3a29-4168-9583-b525922cdce4)

## 2. 개발환경
- 개발보드 : Raspberry pi 3B+
- 운영체제 : Ubuntu Server 20.04 LTS
- 로봇 소프트웨어 플랫폼 : ROS Noetic

## 3. 사용방법
### 3-1. 라이다 실행
- option 1 : 라이다와 rviz 동시 실행
<pre><code>roslaunch ydlidar lidar_view.launch</code></pre>
- option 2 : 라이다만 실행
<pre><code>roslaunch ydlidar lidar.launch</code></pre>
### 3-2. 위험 감지 노드 실행
<pre><code>rosrun ydlidar ydlidar_client</code></pre>
### 3-3. 스피커 노드 실행
<pre><code>rosrun mysound mysoundplay</code></pre>
### 3-4. GPS 노드 실행 (optional)
<pre><code>rosrun app_communicate gps</code></pre>
### 3-5. 속도 계산 노드 실행 (optional)
<pre><code>rosrun app_communicate reed_switch</code></pre>
