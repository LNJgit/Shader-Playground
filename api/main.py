from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pathlib import Path

app = FastAPI()

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