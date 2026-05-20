const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
const fs = require("fs");

const app = express();

app.use(cors());
app.use(bodyParser.json());

let students = [];

/*
========================================
LOAD STUDENTS
========================================
*/

function loadStudents()
{
    students = [];

    if(fs.existsSync("students.txt"))
    {
        const data =
            fs.readFileSync(
                "students.txt",
                "utf-8"
            );

        const lines = data.split("\n");

        lines.forEach(line => {

            if(line.trim() !== "")
            {
                const [
                    name,
                    id,
                    fee,
                    paid
                ] = line.split(",");

                students.push({

                    name:name,

                    id:Number(id),

                    fee:Number(fee),

                    paid:Number(paid)

                });
            }
        });
    }
}

/*
========================================
SAVE STUDENTS
========================================
*/

function saveStudents()
{
    let data = "";

    students.forEach(student => {

        data +=
        `${student.name},${student.id},${student.fee},${student.paid}\n`;

    });

    fs.writeFileSync(
        "students.txt",
        data
    );
}

/*
========================================
HOME ROUTE
========================================
*/

app.get("/",(req,res)=>{

    res.json({

        message:
        "Student Fee Management API Running"

    });

});

/*
========================================
ADD STUDENT
========================================
*/

app.post("/add",(req,res)=>{

    loadStudents();

    const {
        name,
        id,
        fee
    } = req.body;

    /*
    VALIDATION
    */

    if(!name || !id || !fee)
    {
        return res.json({

            message:
            "All fields are required"

        });
    }

    /*
    DUPLICATE ID CHECK
    */

    const found =
        students.find(
            student => student.id == id
        );

    if(found)
    {
        return res.json({

            message:
            "Student ID already exists"

        });
    }

    /*
    ADD STUDENT
    */

    students.push({

        name:name,

        id:Number(id),

        fee:Number(fee),

        paid:0

    });

    saveStudents();

    res.json({

        message:
        "Student Added Successfully"

    });

});

/*
========================================
GET ALL STUDENTS
========================================
*/

app.get("/students",(req,res)=>{

    loadStudents();

    res.json(students);

});

/*
========================================
SEARCH STUDENT BY ID
========================================
*/

app.get("/student/:id",(req,res)=>{

    loadStudents();

    const id =
        Number(req.params.id);

    const student =
        students.find(
            student => student.id == id
        );

    if(!student)
    {
        return res.json({

            error:
            "Student Not Found"

        });
    }

    res.json(student);

});

/*
========================================
SEARCH STUDENT BY NAME
========================================
*/

app.get("/searchByName/:name",(req,res)=>{

    loadStudents();

    const name =
        req.params.name.toLowerCase();

    const filteredStudents =
        students.filter(student =>

        student.name
        .toLowerCase()
        .includes(name)

    );

    if(filteredStudents.length === 0)
    {
        return res.json({

            message:
            "No Student Found"

        });
    }

    res.json(filteredStudents);

});

/*
========================================
UPDATE PAYMENT STATUS
========================================
*/

app.put("/pay/:id",(req,res)=>{

    loadStudents();

    const id =
        Number(req.params.id);

    const student =
        students.find(
            student => student.id == id
        );

    if(!student)
    {
        return res.json({

            message:
            "Student Not Found"

        });
    }

    student.paid = 1;

    saveStudents();

    res.json({

        message:
        "Payment Updated Successfully"

    });

});

/*
========================================
UPDATE FEE
========================================
*/

app.put("/updateFee/:id",(req,res)=>{

    loadStudents();

    const id =
        Number(req.params.id);

    const {fee} = req.body;

    const student =
        students.find(
            student => student.id == id
        );

    if(!student)
    {
        return res.json({

            message:
            "Student Not Found"

        });
    }

    student.fee = Number(fee);

    saveStudents();

    res.json({

        message:
        "Fee Updated Successfully"

    });

});

/*
========================================
GET PAID STUDENTS
========================================
*/

app.get("/paidStudents",(req,res)=>{

    loadStudents();

    const paidStudents =
        students.filter(student =>

        student.paid == 1

    );

    res.json(paidStudents);

});

/*
========================================
GET UNPAID STUDENTS
========================================
*/

app.get("/unpaidStudents",(req,res)=>{

    loadStudents();

    const unpaidStudents =
        students.filter(student =>

        student.paid == 0

    );

    res.json(unpaidStudents);

});

/*
========================================
TOTAL STUDENT COUNT
========================================
*/

app.get("/studentCount",(req,res)=>{

    loadStudents();

    res.json({

        totalStudents:
        students.length

    });

});

/*
========================================
DELETE STUDENT
========================================
*/

app.delete("/delete/:id",(req,res)=>{

    loadStudents();

    const id =
        Number(req.params.id);

    const found =
        students.find(
            student => student.id == id
        );

    if(!found)
    {
        return res.json({

            message:
            "Student Not Found"

        });
    }

    students =
        students.filter(student =>

        student.id != id

    );

    saveStudents();

    res.json({

        message:
        "Student Deleted Successfully"

    });

});

/*
========================================
SERVER
========================================
*/

app.listen(5000,()=>{

    console.log(
        "Server running on port 5000"
    );

});