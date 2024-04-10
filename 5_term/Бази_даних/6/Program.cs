using System;
using System.Data.SqlClient;

class Program
{
    static void Main(string[] args)
    {
        string connectionString = "Data Source=localhost;Initial Catalog=AccessControlDB;Integrated Security=True";

        // Підключення до бази даних
        using (SqlConnection connection = new SqlConnection(connectionString))
        {
            connection.Open();

            // Створення таблиць та початкове наповнення даними
            CreateAndPopulateDatabase(connection);

            Console.WriteLine("Базу даних успішно створено та наповнено початковими даними.");
        }
    }

    static void CreateAndPopulateDatabase(SqlConnection connection)
    {
        // Створення таблиць із відповідними полями
        string createUserTableQuery = "CREATE TABLE Users (UserId INT PRIMARY KEY, Username NVARCHAR(50), Password NVARCHAR(50))";
        string createRoleTableQuery = "CREATE TABLE Roles (RoleId INT PRIMARY KEY, RoleName NVARCHAR(50))";
        string createPermissionTableQuery = "CREATE TABLE Permissions (PermissionId INT PRIMARY KEY, PermissionName NVARCHAR(50))";
        string createObjectTableQuery = "CREATE TABLE Objects (ObjectId INT PRIMARY KEY, ObjectName NVARCHAR(50))";
        string createUserRoleTableQuery = "CREATE TABLE UserRoles (UserId INT, RoleId INT, FOREIGN KEY(UserId) REFERENCES Users(UserId), FOREIGN KEY(RoleId) REFERENCES Roles(RoleId))";
        string createRolePermissionTableQuery = "CREATE TABLE RolePermissions (RoleId INT, PermissionId INT, FOREIGN KEY(RoleId) REFERENCES Roles(RoleId), FOREIGN KEY(PermissionId) REFERENCES Permissions(PermissionId))";
        string createUserObjectPermissionTableQuery = "CREATE TABLE UserObjectPermissions (UserId INT, ObjectId INT, PermissionId INT, FOREIGN KEY(UserId) REFERENCES Users(UserId), FOREIGN KEY(ObjectId) REFERENCES Objects(ObjectId), FOREIGN KEY(PermissionId) REFERENCES Permissions(PermissionId))";

        ExecuteQuery(connection, createUserTableQuery);
        ExecuteQuery(connection, createRoleTableQuery);
        ExecuteQuery(connection, createPermissionTableQuery);
        ExecuteQuery(connection, createObjectTableQuery);
        ExecuteQuery(connection, createUserRoleTableQuery);
        ExecuteQuery(connection, createRolePermissionTableQuery);
        ExecuteQuery(connection, createUserObjectPermissionTableQuery);

        // Наповнення таблиць даними
        // Наповнення таблиці Users
        ExecuteQuery(connection, "INSERT INTO Users (UserId, Username, Password) VALUES (1, 'user1', 'password1')");
        ExecuteQuery(connection, "INSERT INTO Users (UserId, Username, Password) VALUES (2, 'user2', 'password2')");

        // Наповнення таблиці Roles
        ExecuteQuery(connection, "INSERT INTO Roles (RoleId, RoleName) VALUES (1, 'admin')");
        ExecuteQuery(connection, "INSERT INTO Roles (RoleId, RoleName) VALUES (2, 'user')");

        // Наповнення таблиці Permissions
        ExecuteQuery(connection, "INSERT INTO Permissions (PermissionId, PermissionName) VALUES (1, 'read')");
        ExecuteQuery(connection, "INSERT INTO Permissions (PermissionId, PermissionName) VALUES (2, 'write')");

        // Наповнення таблиці Objects
        ExecuteQuery(connection, "INSERT INTO Objects (ObjectId, ObjectName) VALUES (1, 'object1')");
        ExecuteQuery(connection, "INSERT INTO Objects (ObjectId, ObjectName) VALUES (2, 'object2')");

        // Наповнення таблиці UserRoles
        ExecuteQuery(connection, "INSERT INTO UserRoles (UserId, RoleId) VALUES (1, 1)");
        ExecuteQuery(connection, "INSERT INTO UserRoles (UserId, RoleId) VALUES (2, 2)");

        // Наповнення таблиці RolePermissions
        ExecuteQuery(connection, "INSERT INTO RolePermissions (RoleId, PermissionId) VALUES (1, 1)");
        ExecuteQuery(connection, "INSERT INTO RolePermissions (RoleId, PermissionId) VALUES (2, 2)");

        // Наповнення таблиці UserObjectPermissions
        ExecuteQuery(connection, "INSERT INTO UserObjectPermissions (UserId, ObjectId, PermissionId) VALUES (1, 1, 1)");
        ExecuteQuery(connection, "INSERT INTO UserObjectPermissions (UserId, ObjectId, PermissionId) VALUES (2, 2, 2)");
    }

    static void ExecuteQuery(SqlConnection connection, string query)
    {
        SqlCommand command = new SqlCommand(query, connection);
        command.ExecuteNonQuery();
    }
}

