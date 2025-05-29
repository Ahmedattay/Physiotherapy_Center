# 🏥 Physiotherapy Center Simulation  
**Data Structures & Algorithms Project – Cairo University**

## 🔍 Project Overview  
A simulation of a physiotherapy center that models real-world patient scheduling, treatment workflows, and resource allocation using custom data structures (no STL). Designed to optimize efficiency and handle edge cases gracefully.

---

## 🎯 Key Objectives  
- Simulate real-world patient flow: arrival, waiting, treatment, and discharge  
- Optimize resource usage (devices & rooms) via priority-based scheduling  
- Handle edge cases like cancellations, rescheduling, and device failures  

---

## ⚙️ Core Features  

### 👥 Patient Management  
- Categorizes patients as **Early**, **On-Time**, or **Late** (with penalties applied to late arrivals)  
- Supports **rescheduling** for early patients  
- Allows **cancellation** for patients undergoing **exercise therapy** only  

### 💊 Treatment Workflow  
- **Normal Patients (N):** Follow a fixed, predefined treatment sequence  
- **Recovering Patients (R):** Assigned treatment dynamically to improve resource utilization  

### 🛠️ Resource Handling  
- Manages three types of treatment devices:  
  - Electrotherapy (**E**)  
  - Ultrasound (**U**)  
  - Exercise (**X**)  
- Simulates **room capacity limits** and optional **device failures** (bonus feature)  

---

## ✅ Key Takeaways  
This project showcases algorithmic thinking, real-world simulation, and the design of efficient data structures from scratch—emphasizing scheduling, prioritization, and resource optimization.
