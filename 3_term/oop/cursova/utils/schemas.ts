import Ajv, { JTDDataType } from "ajv/dist/jtd"
import { capitalize } from "."

export const ticketTypes = ["Student", "Child", "Adult"] as const

const ticketSchema = {
  elements: {
    properties: {
      key: { type: "int32" },
      name: { type: "string" },
      surname: { type: "string" },
      phone: { type: "int32" },
      ticketType: { enum: ticketTypes },
      ticketExpire: {
        type: "timestamp",
      },
    },
    optionalProperties: {},
  },
} as const

export type Ticket = JTDDataType<typeof ticketSchema>[number]

export type TicketsValidatorReturnType = Array<{
  message: string
  meta: string
}>

const ajv = new Ajv({ allErrors: true })
export const ticketsSerializer = ajv.compileSerializer<Ticket[]>(ticketSchema)
export const ticketsValidator = ajv.compile<Ticket[]>(ticketSchema)

export const getTicketsValidationErrors = (
  tickets: Ticket[]
): TicketsValidatorReturnType => {
  const errors: TicketsValidatorReturnType = []

  const ticketIds = new Set<number>(tickets.map((t) => t.key))
  if (ticketIds.size != tickets.length) {
    errors.push({
      message: "Ticket numbers are not unique",
      meta: 'Make sure tickets have different "key"',
    })
  }

  if (!ticketsValidator(tickets)) {
    errors.push(
      ...(ticketsValidator.errors?.map((e) => ({
        message: e.message
          ? `${capitalize(e.keyword)} error: ${capitalize(e.message)}`
          : "Error",
        meta: `at ${e.instancePath}`,
      })) || [])
    )
  }

  return errors
}
