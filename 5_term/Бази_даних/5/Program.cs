using System;
using Microsoft.Data.Sqlite;

class Program
{
    static void Main(string[] args)
    {
        if (!IsValidArguments(args))
        {
            Console.WriteLine("Потрібно вказати шлях до файлу бази даних (-db) та назву таблиці (-t).");
            return;
        }

        string dbFile = args[1];
        string tableName = args[3];
        bool verbose = args.Length >= 5 && args[4] == "-V";

        using (var connection = new SqliteConnection($"Data Source={dbFile}"))
        {
            connection.Open();

            string selectQuery = $"SELECT * FROM {tableName};";
            using (var command = connection.CreateCommand())
            {
                command.CommandText = selectQuery;
                using (var reader = command.ExecuteReader())
                {
                    if (verbose)
                    {
                        PrintFieldDetails(reader);
                    }

                    PrintData(reader);
                }
            }
        }
    }

    static bool IsValidArguments(string[] args)
    {
        return args.Length >= 4 && args[0] == "-db" && args[2] == "-t";
    }

    static void PrintFieldDetails(SqliteDataReader reader)
    {
        for (int i = 0; i < reader.FieldCount; i++)
        {
            Console.WriteLine($"Поле {reader.GetName(i)}: тип {reader.GetFieldType(i)}");
        }
    }

    static void PrintData(SqliteDataReader reader)
    {
        while (reader.Read())
        {
            for (int i = 0; i < reader.FieldCount; i++)
            {
                Console.Write(reader[i] + "\t");
            }
            Console.WriteLine();
        }
    }
}
