from setuptools import setup, find_packages

setup(
    name='maze_solver',
    version='1.0.0',
    packages=find_packages(where='src'),
    package_dir={'': 'src'},
    entry_points={
        'console_scripts': [
            'maze_solver=main:main',
        ],
    },
    install_requires=[],
    include_package_data=True,
    description='A maze solver implemented in Python',
    author='Your Name',
    author_email='your.email@example.com',
    url='https://github.com/shreyashsaitwal/maze-solver',
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.6',
)
