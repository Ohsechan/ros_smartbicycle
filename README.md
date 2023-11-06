# Smart Bicycle
## 1. 프로젝트 소개
- 수상 이력
  - 2021 한이음 공모전 입선
- 설명
  - 자전거 운전자는 전방을 주시해야 하기 때문에, 측방 또는 후방에서 빠르게 다가오는 물체를 인지하는 것에 어려움이 있습니다.
  - 이 프로젝트에서는 운전자가 안전하게 운전할 수 있는 “스마트자전거”를 제작하였습니다.
  - 2D LiDAR를 이용하여 빠르게 다가오는 물체에 대한 위험을 운전자에게 알립니다.
  - 이외에도 운전자의 안전과 편의를 위한 기능들을 구현하였습니다.
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

## 4. 시스템 상세
### 4-1. 아두이노 시스템 구성도
![Arduino](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/8575d6a7-9f35-4248-87aa-5c9e03d29528)
### 4-2. 라즈베리파이 시스템 구성도
![Raspberry_pi](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/c4636688-99b3-447b-9293-063817f62e5d)
### 4-3. YDLIDAR X4
![lidar](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/f0da4048-7175-44e3-ba58-9c9a41345cd2)
### 4-4. MPU6050 가속도 센서
![가속도센서](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/e689c697-ed33-4a5c-8b59-43fb0fb7e811)
### 4-5. Dot Matrix 32x8 : 방향지시등(좌, 우) 및 수신호(앞질러 가시오, 장애물 조심)
![방향지시등](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/f4efcbd2-390e-4f87-beda-d6afe723f84e)
### 4-6. GPS 수신기(L80-39)
![gps](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/126cf710-ad5b-404c-a671-347686653643)
### 4-7. Reed Switch
![reed](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/42d8255b-a4bc-45a0-b860-da42cfc9bd6f)

