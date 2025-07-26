from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pathlib import Path
from pydantic import BaseModel
from fastapi.staticfiles import StaticFiles

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")

base_dir = Path(__file__).resolve().parent.parent
assets_dir = base_dir / "assets"

# Configure CORS
app.add_middleware(
    CORSMiddleware, 
    allow_origins=["*"],  # Allows all origins
    allow_methods=["*"],  # Allows all methods
    allow_headers=["*"]   # Allows all headers
)

@app.get("/")
async def read_root():
    return {"message": "Welcome to the API!"}

@app.get("/ping")
async def ping():
    return {"message": "pong"}

# Return list of available models
@app.get("/models/")
def list_models():
    model_dir = Path(__file__).parent.parent / "assets" / "models"
    obj_files = sorted([f.name for f in model_dir.glob("*.obj")])
    return {"models": obj_files}

# Model for file upload
class ModelSwitchRequest(BaseModel):
    model_name: str

@app.post("/switch_model/")
def switch_model(request: ModelSwitchRequest):
    model_name = request.model_name
    model_path = assets_dir / "current_model.txt"
    
    if not model_name.endswith(".obj"):
        return {"error": "Model must be an .obj file"}

    current_model = model_path.read_text().strip() if model_path.exists() else None
    if current_model == model_name:
        return {"message": f"Model '{model_name}' is already set."}
    
    with model_path.open("w") as f:
        f.write(model_name)
    
    return {"message": f"Switched to model: {model_name}"}