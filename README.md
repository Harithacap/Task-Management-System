<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Task Management System</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 20px;
      padding: 0;
    }
    .container {
      max-width: 600px;
      margin: auto;
    }
    .task {
      padding: 10px;
      margin: 10px 0;
      border: 1px solid #ccc;
      border-radius: 5px;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    .task.completed {
      background-color: #e0ffe0;
      text-decoration: line-through;
    }
    .buttons {
      display: flex;
      gap: 5px;
    }
    button {
      padding: 5px 10px;
      cursor: pointer;
    }
    #filter-options {
      margin: 10px 0;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Task Management System</h1>
    <div>
      <input type="text" id="task-title" placeholder="Task Title" />
      <input type="date" id="task-due-date" />
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
            <strong>${task.title}</strong> <br />
            Due: ${task.dueDate} | Priority: ${task.priority === '1' ? 'High' : task.priority === '2' ? 'Medium' : 'Low'}
          </div>
          <div class="buttons">
            <button onclick="markComplete(${index})">${task.isComplete ? 'Undo' : 'Complete'}</button>
            <button onclick="deleteTask(${index})">Delete</button>
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
