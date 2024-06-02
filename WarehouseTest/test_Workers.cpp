#include "../WarehouseLib/Workers.h"
#include <gtest/gtest.h>

TEST(WorkerTest, ConstructorAndGetters) {
    Worker worker("John", "Doe", 30, Post::WarehouseManagement, 5000.0, 5);
    EXPECT_EQ(worker.getName(), "John");
    EXPECT_EQ(worker.getLastName(), "Doe");
    EXPECT_EQ(worker.getAge(), 30);
    EXPECT_EQ(worker.getPost(), Post::WarehouseManagement);
    EXPECT_EQ(worker.getSalary(), 5000.0);
    EXPECT_EQ(worker.getSeniority(), 5);
}

TEST(WorkerTest, AddOpinionAndGetOpinions) {
    Worker worker("Jane", "Doe", 28, Post::PhysicalLabor, 3000.0, 2);
    worker.addOpinion("Great worker");
    worker.addOpinion("Always on time");
    EXPECT_EQ(worker.getOpinions(), "Great worker\nAlways on time\n");
}

TEST(WorkerTest, GetPost) {
    Worker worker("Alice", "Smith", 25, Post::Other, 4000.0, 3);
    EXPECT_EQ(worker.getPost(), Post::Other);
}

TEST(WorkerTest, GetSalary) {
    Worker worker("Bob", "Johnson", 40, Post::WarehouseManagement, 6000.0, 10);
    EXPECT_EQ(worker.getSalary(), 6000.0);
}

TEST(WorkerTest, GetSeniority) {
    Worker worker("Charlie", "Brown", 35, Post::PhysicalLabor, 3500.0, 7);
    EXPECT_EQ(worker.getSeniority(), 7);
}

TEST(WorkerTest, OperatorSquareBrackets) {
    Worker worker("David", "White", 32, Post::Other, 4500.0, 4);
    worker.addOpinion("Good team player");
    EXPECT_EQ(worker[0], "Good team player");
}

TEST(WorkerTest, OperatorSquareBracketsOutOfRange) {
    Worker worker("Eve", "Black", 29, Post::WarehouseManagement, 5000.0, 6);
    worker.addOpinion("Reliable");
    EXPECT_THROW(worker[1], std::out_of_range);
}

TEST(WorkerTest, AddOpinionAndRetrieve) {
    Worker worker("Frank", "Green", 45, Post::PhysicalLabor, 4000.0, 20);
    worker.addOpinion("Experienced");
    worker.addOpinion("Mentor to others");
    EXPECT_EQ(worker[0], "Experienced");
    EXPECT_EQ(worker[1], "Mentor to others");
}

TEST(ManagerTest, ConstructorAndGetters) {
    Manager manager("Gary", "King", 50, 8000.0, 25);
    EXPECT_EQ(manager.getName(), "Gary");
    EXPECT_EQ(manager.getLastName(), "King");
    EXPECT_EQ(manager.getAge(), 50);
    EXPECT_EQ(manager.getSalary(), 8000.0);
    EXPECT_EQ(manager.getSeniority(), 25);
}

TEST(ManagerTest, EmployWorker) {
    Manager manager("Helen", "Queen", 55, 9000.0, 30);
    Worker worker("Ian", "Prince", 30, Post::Other, 4000.0, 5);
    manager.employWorker(&worker);
    EXPECT_EQ(manager.generateReport(), "Ian Prince\n");
}

TEST(ManagerTest, DismissWorker) {
    Manager manager("Jack", "Knight", 60, 10000.0, 35);
    Worker worker("Kelly", "Bishop", 28, Post::WarehouseManagement, 4500.0, 4);
    manager.employWorker(&worker);
    manager.dismissWorker(&worker);
    EXPECT_EQ(manager.generateReport(), "");
}

TEST(ManagerTest, GenerateReport) {
    Manager manager("Liam", "Emperor", 45, 8500.0, 20);
    Worker worker1("Mia", "Countess", 30, Post::PhysicalLabor, 3000.0, 5);
    Worker worker2("Noah", "Marquis", 32, Post::WarehouseManagement, 4000.0, 7);
    manager.employWorker(&worker1);
    manager.employWorker(&worker2);
    EXPECT_EQ(manager.generateReport(), "Mia Countess\nNoah Marquis\n");
}
