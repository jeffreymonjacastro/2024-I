import React, {useState, useEffect} from 'react'
import { fetchRides, deleteRide } from '../services/api'
import { useNavigate } from 'react-router-dom'

const Rides = () => {
  const [data, setData] = useState([])
  const [change, setChange] = useState(0)
  const navigate = useNavigate();

  const getData = async() => {
    const res = await fetchRides(0)

    setData(res.data.content)

    console.log(data);
  }

  const rideDelete = async(rideId) => {
    const res = await deleteRide(rideId)

    console.log(res);

    setChange(change + 1)
  }

  useEffect(() => {
    getData()
    console.log(change);
  }, [change])


  return (
    <>
      <h1>Rides</h1>

      <div>
      {
      data.map((ride, index) => (
        <div key={index} className='ride'>
          <p>{ride.id}  </p>
          <p>{ride.originName}  </p>
          <p>{ride.destinationName}  </p>
          <p>{ride.departureDate}  </p>
          <p>{ride.price}</p>
          <button
            onClick = { () => rideDelete(ride.id) }
          > Delete </button>
        </div>
        ))
      }
      </div>
    </>
  )
}

export default Rides