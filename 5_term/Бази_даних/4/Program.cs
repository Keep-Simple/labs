using System;
using Microsoft.Data.Sqlite;

class Program
{
    static void Main()
    {
        string connectionString = "Data Source=suppliers.db";

        using (var connection = new SqliteConnection(connectionString))
        {
            connection.Open();

            CreateSuppliersTable(connection);
            InsertSupplier(connection, "Company A", "Address 1");
            InsertSupplier(connection, "Company B");

            DisplaySuppliers(connection);
        }
    }

    static void CreateSuppliersTable(SqliteConnection connection)
    {
        string createTableQ = @"
            CREATE TABLE IF NOT EXISTS suppliers (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                address TEXT DEFAULT 'Not provided'
            );";

        ExecuteNonQuery(connection, createTableQ);
    }

    static void InsertSupplier(SqliteConnection connection, string name, string address = "Not provided")
    {
        string insertQ = "INSERT INTO suppliers (name, address) VALUES (@name, @address);";

        using (var command = connection.CreateCommand())
        {
            command.CommandText = insertQ;
            command.Parameters.AddWithValue("@name", name);
            command.Parameters.AddWithValue("@address", address);
            command.ExecuteNonQuery();
        }
    }

    static void DisplaySuppliers(SqliteConnection connection)
    {
        string selectAllQ = "SELECT * FROM suppliers;";

        using (var command = connection.CreateCommand())
        {
            command.CommandText = selectAllQ;
            using (var reader = command.ExecuteReader())
            {
                Console.WriteLine("id\tname\taddress");
                while (reader.Read())
                {
                    Console.WriteLine($"{reader["id"]}\t{reader["name"]}\t{reader["address"]}");
                }
            }
        }
    }

    static void ExecuteNonQuery(SqliteConnection connection, string query)
    {
        using (var command = connection.CreateCommand())
        {
            command.CommandText = query;
            command.ExecuteNonQuery();
        }
    }
}
