from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

# Placeholder for sensor data
sensor_data = {"temperature": "Waiting...", "moisture": "Waiting..."}

@app.route('/')
def index():
    return render_template('index.html', data=sensor_data)

@app.route('/update', methods=['POST'])
def update_data():
    global sensor_data
    data = request.json
    sensor_data["temperature"] = data.get("temperature", "N/A")
    sensor_data["moisture"] = data.get("moisture", "N/A")
    return jsonify({"status": "success", "data": sensor_data})

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
