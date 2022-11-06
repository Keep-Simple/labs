import Ajv, { JTDDataType } from "ajv/dist/jtd"
import { capitalize } from "."

const ticketSchema = {
  elements: {
    properties: {
      key: { type: "int32" },
      name: { type: "string" },
      surname: { type: "string" },
      phone: { type: "uint32" },
      ticketType: { enum: ["Student", "Child", "Adult"] },
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

export const customTicketValidators: Partial<
  Record<keyof Ticket, (s: Ticket) => string[]>
> = {
  // grades: (r) => {
  //   const messages = []
  //   const has_not_number = r.grades.some((g) => !/^-?\d+$/.test(g.toString()))
  //   const out_of_range = r.grades.map(Number).some((m) => m < 1 || m > 5)
  //   if (has_not_number) messages.push(`Grades must be coma separated numbers`)
  //   if (out_of_range) messages.push(`Grade must be in range of 1-5`)
  //   return messages
  // },
} as const

const ajv = new Ajv({ allErrors: true })
export const ticketsSerializer = ajv.compileSerializer<Ticket[]>(ticketSchema)
const _compiledValidator = ajv.compile<Ticket[]>(ticketSchema)

export const ticketsValidator = (
  tickets: Ticket[]
): TicketsValidatorReturnType => {
  _compiledValidator(tickets)

  const errors: TicketsValidatorReturnType =
    _compiledValidator.errors?.map((e) => ({
      message: e.message
        ? `${capitalize(e.keyword)} error: ${capitalize(e.message)}`
        : "Error",
      meta: `at ${e.instancePath}`,
    })) || []

  tickets.forEach((ticket) =>
    Object.entries(customTicketValidators).map(
      ([propertyName, propertyValidator]) => {
        errors.push(
          ...propertyValidator(ticket).map((e) => ({
            message: e,
            meta: `at ${propertyName} of ${JSON.stringify(ticket)}`,
          }))
        )
      }
    )
  )

  return errors
}
