#include "../WarehouseLib/Workers.h"
#include <gtest/gtest.h>

TEST(WorkerTest, ConstructorAndGetters) {
    Worker worker("Jan", "Kowalski", 30, Post::WarehouseManagement, 5000.0, 5);
    EXPECT_EQ(worker.getName(), "Jan");
    EXPECT_EQ(worker.getLastName(), "Kowalski");
    EXPECT_EQ(worker.getAge(), 30);
    EXPECT_EQ(worker.getPost(), Post::WarehouseManagement);
    EXPECT_DOUBLE_EQ(worker.getSalary(), 5000.0);
    EXPECT_EQ(worker.getExperience(), 5);
}

TEST(WorkerTest, AddOpinionAndGetOpinions) {
    Worker worker("Ewa", "Grzyb", 28, Post::PhysicalLabor, 3000.0, 2);
    worker.addOpinion("Œwietny pracownik");
    worker.addOpinion("Zawsze punktualna");
    EXPECT_EQ(worker.getOpinions(), "Opinions:\n1. Œwietny pracownik\n2. Zawsze punktualna\n");
}

TEST(WorkerTest, GetPost) {
    Worker worker("Alicja", "Nowak", 25, Post::Other, 4000.0, 3);
    EXPECT_EQ(worker.getPost(), Post::Other);
}

TEST(WorkerTest, GetSalary) {
    Worker worker("Robert", "Wiœniewski", 40, Post::WarehouseManagement, 6000.0, 10);
    EXPECT_DOUBLE_EQ(worker.getSalary(), 6000.0);
}

TEST(WorkerTest, GetExperience) {
    Worker worker("Karol", "Zieliñski", 35, Post::PhysicalLabor, 3500.0, 7);
    EXPECT_EQ(worker.getExperience(), 7);
}

TEST(WorkerTest, OperatorSquareBrackets) {
    Worker worker("Dawid", "Bia³y", 32, Post::Other, 4500.0, 4);
    worker.addOpinion("Dobry gracz zespo³owy");
    EXPECT_EQ(worker[0], "Dobry gracz zespo³owy");
}

TEST(WorkerTest, OperatorSquareBracketsOutOfRange) {
    Worker worker("Ewa", "Czarny", 29, Post::WarehouseManagement, 5000.0, 6);
    worker.addOpinion("Niezawodna");
    EXPECT_THROW(worker[1], std::out_of_range);
}

TEST(WorkerTest, AddOpinionAndRetrieve) {
    Worker worker("Franciszek", "Zielony", 45, Post::PhysicalLabor, 4000.0, 20);
    worker.addOpinion("Doœwiadczony");
    worker.addOpinion("Mentor dla innych");
    EXPECT_EQ(worker[0], "Doœwiadczony");
    EXPECT_EQ(worker[1], "Mentor dla innych");
}

TEST(ManagerTest, ConstructorAndGetters) {
    Manager manager("Grzegorz", "Król", 50, 8000.0, 25);
    EXPECT_EQ(manager.getName(), "Grzegorz");
    EXPECT_EQ(manager.getLastName(), "Król");
    EXPECT_EQ(manager.getAge(), 50);
    EXPECT_DOUBLE_EQ(manager.getSalary(), 8000.0);
    EXPECT_EQ(manager.getExperience(), 25);
}

TEST(ManagerTest, EmployWorker) {
    Manager manager("Helena", "Królowa", 55, 9000.0, 30);
    Worker worker("Igor", "Ksi¹¿ê", 30, Post::Other, 4000.0, 5);
    manager.employWorker(&worker);
    EXPECT_EQ(manager.generateReport(), "Employee performance report:\nIgor Ksi¹¿ê\nOpinions:\n");
}

TEST(ManagerTest, DismissWorker) {
    Manager manager("Jakub", "Rycerz", 60, 10000.0, 35);
    Worker worker("Katarzyna", "Biskup", 28, Post::WarehouseManagement, 4500.0, 4);
    manager.employWorker(&worker);
    manager.dismissWorker(&worker);
    EXPECT_EQ(manager.generateReport(), "Employee performance report:\n");
}

TEST(ManagerTest, GenerateReport) {
    Manager manager("Leon", "Cesarz", 45, 8500.0, 20);
    Worker worker1("Maria", "Hrabina", 30, Post::PhysicalLabor, 3000.0, 5);
    Worker worker2("Noe", "Markiz", 32, Post::WarehouseManagement, 4000.0, 7);
    manager.employWorker(&worker1);
    manager.employWorker(&worker2);
    EXPECT_EQ(manager.generateReport(), "Employee performance report:\nMaria Hrabina\nOpinions:\nNoe Markiz\nOpinions:\n");
}
