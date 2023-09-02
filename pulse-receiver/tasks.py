import pathlib
import time
from invoke import task

elf_file = pathlib.Path("build", "pulse-receiver.elf")

@task
def upload(c):
    if c.run("picotool info", warn=True).failed:
        c.run("reset-bootsel /dev/ttyACM0", warn=True)
        time.sleep(3)
    c.run(f"picotool load {elf_file}")
    c.run(f"picotool reboot")

@task
def build(c):
    with c.cd("build"):
        c.run("cmake ..")
        c.run("make")