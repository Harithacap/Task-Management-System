<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Task Management System</title>
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;600&display=swap" rel="stylesheet">
  <style>
    body {
      font-family: 'Poppins', sans-serif;
      margin: 0;
      padding: 0;
      background-color: #f9f9f9;
      color: #333;
    }
    .container {
      max-width: 800px;
      margin: 50px auto;
      background: #fff;
      padding: 20px;
      border-radius: 10px;
      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    }
    h1 {
      text-align: center;
      color: #007bff;
    }
    .input-group {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin-bottom: 20px;
    }
    .input-group input,
    .input-group select {
      flex: 1;
      padding: 10px;
      font-size: 16px;
      border: 1px solid #ccc;
      border-radius: 5px;
    }
    .input-group button {
      background-color: #007bff;
      color: #fff;
      border: none;
      padding: 10px 20px;
      font-size: 16px;
      border-radius: 5px;
      cursor: pointer;
      transition: background-color 0.3s;
    }
    .input-group button:hover {
      background-color: #0056b3;
    }
    #filter-options {
      text-align: center;
      margin-bottom: 20px;
    }
    #filter-options button {
      background-color: #6c757d;
      color: #fff;
      border: none;
      padding: 8px 15px;
      font-size: 14px;
      border-radius: 5px;
      cursor: pointer;
      margin: 0 5px;
      transition: background-color 0.3s;
    }
    #filter-options button:hover {
      background-color: #5a6268;
    }
    .task {
      display: flex;
      justify-content: space-between;
      align-items: center;
      background: #f8f9fa;
      padding: 15px;
      margin-bottom: 10px;
      border: 1px solid #ddd;
      border-radius: 5px;
      transition: box-shadow 0.3s;
    }
    .task:hover {
      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    }
    .task.completed {
      background-color: #e8f5e9;
      color: #388e3c;
      text-decoration: line-through;
    }
    .task strong {
      color: #007bff;
    }
    .buttons button {
      background-color: #17a2b8;
      color: #fff;
      border: none;
      padding: 8px 10px;
      font-size: 14px;
      border-radius: 5px;
      cursor: pointer;
      transition: background-color 0.3s;
    }
    .buttons button:hover {
      background-color: #138496;
    }
    .buttons button.delete {
      background-color: #dc3545;
    }
    .buttons button.delete:hover {
      background-color: #c82333;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Task Management System</h1>
    <div class="input-group">
      <input type="text" id="task-title" placeholder="Task Title">
      <input type="date" id="task-due-date">
      <select id="task-priority">
        <option value="1">High</option>
        <option value="2">Medium</option>
        <option value="3">Low</option>
      </select>
      <button onclick="addTask()">Add Task</button>
    </div>
    <div id="filter-options">
      <label>Filter: </label>
      <button onclick="filterTasks('all')">All</button>
      <button onclick="filterTasks('completed')">Completed</button>
      <button onclick="filterTasks('incomplete')">Incomplete</button>
    </div>
    <div id="task-list"></div>
  </div>

  <script>
    let tasks = [];

    function addTask() {
      const title = document.getElementById('task-title').value;
      const dueDate = document.getElementById('task-due-date').value;
      const priority = document.getElementById('task-priority').value;

      if (!title || !dueDate) {
        alert('Please fill in all fields!');
        return;
      }

      const task = {
        title,
        dueDate,
        priority,
        isComplete: false
      };
      tasks.push(task);

      document.getElementById('task-title').value = '';
      document.getElementById('task-due-date').value = '';
      renderTasks();
    }

    function renderTasks(filter = 'all') {
      const taskList = document.getElementById('task-list');
      taskList.innerHTML = '';

      let filteredTasks = tasks;
      if (filter === 'completed') {
        filteredTasks = tasks.filter(task => task.isComplete);
      } else if (filter === 'incomplete') {
        filteredTasks = tasks.filter(task => !task.isComplete);
      }

      filteredTasks.forEach((task, index) => {
        const taskDiv = document.createElement('div');
        taskDiv.className = `task ${task.isComplete ? 'completed' : ''}`;
        taskDiv.innerHTML = `
          <div>
            <strong>${task.title}</strong> <br>
            Due: ${task.dueDate} | Priority: ${task.priority === '1' ? 'High' : task.priority === '2' ? 'Medium' : 'Low'}
          </div>
          <div class="buttons">
            <button onclick="markComplete(${index})">${task.isComplete ? 'Undo' : 'Complete'}</button>
            <button class="delete" onclick="deleteTask(${index})">Delete</button>
          </div>
        `;
        taskList.appendChild(taskDiv);
      });
    }

    function markComplete(index) {
      tasks[index].isComplete = !tasks[index].isComplete;
      renderTasks();
    }

    function deleteTask(index) {
      tasks.splice(index, 1);
      renderTasks();
    }

    function filterTasks(filter) {
      renderTasks(filter);
    }
  </script>
</body>
</html>

