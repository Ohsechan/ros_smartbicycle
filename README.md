# Smart Bicycle
## 1. 프로젝트 요약
### 1-1. 설명
자전거 운전자는 항상 전방을 주시하기 때문에 측방과 후방에서 다가오는 물체를 인식하지 못한다. 빠르게 다가오는 물체에 대한 충돌 위험을 미리 알릴 수 있다면 운전자는 충돌 사고에 미리 대비할 수 있을 것이다.
본 프로젝트에서는 자전거에 LiDAR 센서를 부착하여 빠르게 다가오는 물체의 방향과 거리를 운전자에게 음성으로 안내하는 기능을 구현하였다. 또한 방향지시등 기능, 현재 위치 정보, 현재 속도 정보 등의 운전자의 편의를 위한 기능도 구현하였다.
### 1-2. 수상이력
- 2021 한이음 공모전 입선
### 1-3. 개발 규모
- 인원 : 3명
- 일시 : 2021.04 ~ 2021.11
### 1-4. 개발환경
- Ubuntu 20.04 Server
- ROS Noetic
- C++ : YDLIDAR SDK
- Python
### 1-5. 하드웨어
- Raspberry pi 3B+
- Arduino nano
- YDLIDAR X4
- MPU6050
- Dot Matrix 32x8
- L80-39 GPS 모듈
- 리드스위치

## 2. 프로젝트 구현
### 2-1. 데모 영상
[![youtube playlist](http://img.youtube.com/vi/WzGiYVAovKw/0.jpg)](https://www.youtube.com/playlist?list=PLx5EbqT-6Y0-vhDGhUZjxdHfV_A648O1l)
### 3-1. 아두이노 시스템 구성도
![Arduino](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/8575d6a7-9f35-4248-87aa-5c9e03d29528)
### 3-2. 라즈베리파이 시스템 구성도
![Raspberry_pi](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/c4636688-99b3-447b-9293-063817f62e5d)
### 3-3. 주변 환경 감지를 위한 YDLIDAR X4
![lidar](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/f0da4048-7175-44e3-ba58-9c9a41345cd2)
### 3-4. 핸들 방향 감지를 위한 MPU6050 가속도 센서
![가속도센서](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/e689c697-ed33-4a5c-8b59-43fb0fb7e811)
### 3-5. 후방 지시등을 위한 Dot Matrix 32x8 : 방향지시등(좌, 우) 및 수신호(앞질러 가시오, 장애물 조심)
![방향지시등](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/f4efcbd2-390e-4f87-beda-d6afe723f84e)
### 3-6. 현재 위치 표시를 위한 GPS 수신기(L80-39)
![gps](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/126cf710-ad5b-404c-a671-347686653643)
### 3-7. 현재 속도 표시를 위한 Reed Switch
![reed](https://github.com/Ohsechan/ros_smartbicycle/assets/77317210/42d8255b-a4bc-45a0-b860-da42cfc9bd6f)

## 4. 실행 방법
### 4-1. 라이다 실행
- option 1 : 라이다와 rviz 동시 실행
<pre><code>roslaunch ydlidar lidar_view.launch</code></pre>
- option 2 : 라이다만 실행
<pre><code>roslaunch ydlidar lidar.launch</code></pre>
### 4-2. 위험 감지 노드 실행
<pre><code>rosrun ydlidar ydlidar_client</code></pre>
### 4-3. 스피커 노드 실행
<pre><code>rosrun mysound mysoundplay</code></pre>
### 4-4. GPS 노드 실행 (optional)
<pre><code>rosrun app_communicate gps</code></pre>
### 4-5. 속도 계산 노드 실행 (optional)
<pre><code>rosrun app_communicate reed_switch</code></pre>
