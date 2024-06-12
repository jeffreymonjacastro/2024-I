import React, { useState, useEffect } from 'react'
import { getRides } from '../services/api'

const Dashboard = () => {
  const [rides, setRides] = useState([])

  const fetch = async() => {
    const res = await getRides(0, 10)
    setRides(res.data.content)
    console.log(res.data.content);
  }

  useEffect(() => {
    fetch()
  }, [])

  return (
    <>
      <div>Dashboard</div>
      <button>
        Click me!
      </button>
      <div>
        {rides.map((ride, index) => (
          <div key={index}>
            <p>{ride.id}</p>
            <p>{ride.originName}</p>
            <p>{ride.destinationName}</p>
            <p>{ride.departureDate}</p>
            <p>{ride.price}</p>
          </div>
        ))}
      </div>
    </>
  )
}

export default Dashboard